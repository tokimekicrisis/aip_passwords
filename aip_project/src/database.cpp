#include "database/database.h"
#include "sqlite3.h"

#include <QCryptographicHash>

#include <iostream>
#include <vector>

/**
 * Создает таблицу в БД, где будет храниться главный пароль.

 * @return bool Успех/не успех создания таблицы.
 */
bool Database::createMaster() {
  char* errMsg;
  const char* sql = "CREATE TABLE IF NOT EXISTS MASTER_PASSWORD ("
                    "HASH TEXT NOT NULL);";
  return sqlite3_exec(db_, sql, nullptr, nullptr, &errMsg) == SQLITE_OK;
}

/**
 * Проверяет, существует ли таблица для главного пароля.
 * Если существует и не пустая, то считается, что приложение
 * запущено не впервые.
 * Иначе - впервые.
 *
 * @return bool Первый/не первый запуск.
 */
bool Database::isFirstRun() {
  sqlite3_stmt* stmt;
  const char* query = "SELECT name FROM sqlite_master WHERE type='table' AND name='MASTER_PASSWORD';";
  if (sqlite3_prepare_v2(db_, query, -1, &stmt, nullptr) != SQLITE_OK) {
      return true;
  }
  bool exists = (sqlite3_step(stmt) == SQLITE_ROW);
  sqlite3_finalize(stmt);

  if (!exists) {
      return true;
  }
  query = "SELECT COUNT(*) FROM MASTER_PASSWORD;";
  if (sqlite3_prepare_v2(db_, query, -1, &stmt, nullptr) != SQLITE_OK) {
      return true;
  }

  bool has_pw = (sqlite3_step(stmt) == SQLITE_ROW && sqlite3_column_int(stmt, 0) > 0);
  sqlite3_finalize(stmt);
  return !has_pw;
}

/**
 * Задает главный пароль, хэширует и сохраняет его в БД.
 *
 * @return bool Успех/не успех сохранения пароля.
 */
bool Database::setMaster(const QString& password)
{
  if (!createMaster()) {
    return false;
  }

  char* errMsg;
  const char* clear = "DELETE FROM MASTER_PASSWORD;";
  if (sqlite3_exec(db_, clear, nullptr, nullptr, &errMsg) != SQLITE_OK) {
    sqlite3_free(errMsg);
    return false;
  }

  QByteArray hash = QCryptographicHash::hash(
                        password.toUtf8(),
                        QCryptographicHash::Sha256
                        ).toHex();

  sqlite3_stmt* stmt;
  const char* insert = "INSERT INTO MASTER_PASSWORD (HASH) VALUES (:HASH);";

  if (sqlite3_prepare_v2(db_, insert, -1, &stmt, nullptr) != SQLITE_OK) {
    return false;
  }

  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":HASH"),
                    hash.constData(), -1, SQLITE_TRANSIENT);

  bool success = (sqlite3_step(stmt) == SQLITE_DONE);
  sqlite3_finalize(stmt);

  return success;
}

/**
 * Проверяет, соответствует ли введенный пароль
 * сохраненному в БД.
 *
 * @return bool Соответствие/несоответствие пароля.
 */
bool Database::verifyMaster(const QString& password)
{
  sqlite3_stmt* stmt;
  const char* query = "SELECT HASH FROM MASTER_PASSWORD LIMIT 1;";

  if (sqlite3_prepare_v2(db_, query, -1, &stmt, nullptr) != SQLITE_OK) {
    return false;
  }

  if (sqlite3_step(stmt) != SQLITE_ROW) {
    sqlite3_finalize(stmt);
    return false;
  }

  const char* stored = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
  QByteArray input = QCryptographicHash::hash(
                              password.toUtf8(),
                              QCryptographicHash::Sha256
                              ).toHex();

  bool match = (input == QByteArray(stored));
  sqlite3_finalize(stmt);

  return match;
}

/**
 * Получает главный пароль из БД
 * (для использования как ключ для
 * шифрования остальных паролей).
 *
 * @return std::string Пароль.
 */
std::string Database::getMaster() {
  sqlite3_stmt* stmt;
  const char* query = "SELECT HASH FROM MASTER_PASSWORD LIMIT 1;";

  if (sqlite3_prepare_v2(db_, query, -1, &stmt, nullptr) != SQLITE_OK) {
    throw std::runtime_error("невозможно найти ключ");
  }

  if (sqlite3_step(stmt) != SQLITE_ROW) {
    sqlite3_finalize(stmt);
    throw std::runtime_error("ключ не найден");
  }

  const char* key = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
  std::string result = key;
  sqlite3_finalize(stmt);

  return result;
}

/**
 * Шифрование паролей методом XOR.
 *
 * @param input Шифруемый пароль.
 * @return std::string Результат.
 */
std::string Database::xorEncrypt(const std::string& input) {
  std::string key = getMaster();
  std::string output = input;
  for (size_t i = 0; i < input.size(); ++i) {
      output[i] = input[i] ^ key[i % key.size()];
  }
  return output;
}

/**
 * Открытие БД.
 * Если БД не открывается, падает с ошибкой.
 * Иначе создает таблицу, если она уже не существует.
 * Если по какой-то причине запрос создать таблицу не сработал,
 * тоже выдает ошибку.
 *
 * @param filename Путь к базе данных.
 */
Database::Database(const char* filename) {
  if (sqlite3_open(filename, &db_) != SQLITE_OK) {
    throw std::runtime_error(sqlite3_errmsg(db_));
  }

  char* errMsg;
  char* sql = "CREATE TABLE IF NOT EXISTS PASSWORDS(" 
              "ID INTEGER PRIMARY KEY,"
              "SITE TEXT NOT NULL,"
              "PASSWORD TEXT NOT NULL,"
              "CATEGORY TEXT,"
              "COMMENT TEXT)";

  int rc = sqlite3_exec(db_, sql, NULL, 0, &errMsg);
  if(rc != SQLITE_OK){
    sqlite3_free(errMsg);
  } 
}                

/**
 * Закрытие БД.
 */
Database::~Database() {
  sqlite3_close(db_);
}

/**
 * Добавление записи в БД.
 * При добавлении пароль шифруется.
 *
 * @param site Сайт.
 * @param pw Пароль.
 * @param cat Категория.
 * @param cmt Комментарий.
 * @return bool true, если все прошло успешно, в противном случае false.
 */
bool Database::insertData(const char* site, const char* pw,
                          const char* cat, const char* cmt) {
  sqlite3_stmt* stmt;
  const char* query = "INSERT INTO PASSWORDS (SITE, PASSWORD, CATEGORY, COMMENT)"
                      "VALUES (:SITE, :PASSWORD, :CATEGORY, :COMMENT);";
  
  if (sqlite3_prepare_v2(db_, query, -1, &stmt, nullptr) != SQLITE_OK) {
    return false;
  }

  std::string encrypted = xorEncrypt(pw);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":SITE"), site, -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":PASSWORD"), encrypted.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":CATEGORY"), cat, -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":COMMENT"), cmt, -1, SQLITE_TRANSIENT);
  
  int rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    return false;
  } 

  sqlite3_finalize(stmt);
  return true;
}

/**
 * Изменение существующей записи в БД.
 * При изменении пароль также шифруется.
 *
 * @param id ID нужной записи.
 * @param site Сайт.
 * @param pw Пароль.
 * @param cat Категория.
 * @param cmt Комментарий.
 * @return bool true, если все прошло успешно, в противном случае false.
 */
bool Database::updateData(const char* id,
                          const char* site, const char* pw,
                          const char* cat, const char* cmt) {
  sqlite3_stmt* stmt;
  const char* query = "UPDATE PASSWORDS "
                      "SET SITE = :SITE, PASSWORD = :PASSWORD, "
                      "CATEGORY = :CATEGORY, COMMENT = :COMMENT "
                      "WHERE ID = :ID";
  
  if (sqlite3_prepare_v2(db_, query, -1, &stmt, nullptr) != SQLITE_OK) {
    return false;
  }

  std::string encrypted = xorEncrypt(pw);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":SITE"), site, -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":PASSWORD"), encrypted.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":CATEGORY"), cat, -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":COMMENT"), cmt, -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":ID"), id, -1, SQLITE_TRANSIENT);

    
  int rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    return false;
  } 
  sqlite3_finalize(stmt);
  return true;
}

/**
 * Удаление существующей записи в БД.
 *
 * @param id ID нужной записи.
 * @return bool true, если все прошло успешно, в противном случае false.
 */
bool Database::deleteData(const char* id) {
  sqlite3_stmt* stmt;
  const char* query = "DELETE FROM PASSWORDS WHERE ID = :ID;";
  
  if (sqlite3_prepare_v2(db_, query, -1, &stmt, nullptr) != SQLITE_OK) {
    return false;
  }

  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":ID"), id, -1, SQLITE_TRANSIENT);
  
  int rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    std::cerr << "error: " << sqlite3_errmsg(db_) << std::endl;
    return false;
  } 
  sqlite3_finalize(stmt);
  return true;
}

/**
 * Получение записей из БД: либо по поисковому запросу, либо по категории.
 * При извлечении пароль расшифровывается.
 * Если оба параметра равны nullptr, просто выдает все записи.
 * Иначе выдает записи, где сайт или комментарий содержит данный запрос,
 * либо где категория равна данной.
 *
 * @param search_term Поисковой запрос.
 * @param cat Категория.
 * @return std::vector<std::vector<std::string>> Соответствующие запросу записи.
 */
std::vector<std::vector<std::string>> Database::extractData(const char* search_term,
                                                            const char* cat) {
  sqlite3_stmt* stmt;
  std::string query = "SELECT * FROM PASSWORDS";
  
  if (search_term != nullptr || cat != nullptr) {
  }

  if (search_term != nullptr) {
    query += " WHERE (SITE LIKE :TERM OR COMMENT LIKE :TERM)";
    if (cat != nullptr) {
      query += " AND ";
    }
  }

  if (cat != nullptr) {
    query += " WHERE (CATEGORY = :CAT)";
  }

  if (sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    throw std::runtime_error(sqlite3_errmsg(db_));
  }

  if (search_term != nullptr) {
    std::string term = "%" + std::string(search_term) + "%";
    sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":TERM"), term.c_str(), -1, SQLITE_TRANSIENT);
  }

  if (cat != nullptr) {
    sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":CAT"), cat, -1, SQLITE_TRANSIENT);
  }

  int col_count = sqlite3_column_count(stmt);
  std::vector<std::vector<std::string>> results;
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    std::vector<std::string> row;
    for (int i = 0; i < col_count; i++) {
      const char* val = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
        if (i == 2) {
          std::string decrypted = xorEncrypt(val);
          row.push_back(decrypted);
        } else {
          row.push_back(val);
        }
    }
    results.push_back(row);
  }
  
  sqlite3_finalize(stmt);
  return results;
}
