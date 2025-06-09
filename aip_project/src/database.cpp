#include "database/database.h"

#include "sqlite3.h"

#include <iostream>
#include <vector>

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
    std::cout << "Error in executing SQL: %s \n" << errMsg << std::endl;
    sqlite3_free(errMsg);
  } else {
    std::cout << "table made successfully" << std::endl;
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

  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":SITE"), site, -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":PASSWORD"), pw, -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":CATEGORY"), cat, -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":COMMENT"), cmt, -1, SQLITE_TRANSIENT);
  
  int rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    std::cerr << "error: " << sqlite3_errmsg(db_) << std::endl;
    return false;
  } else {
    std::cout << "data inserted successfully" << std::endl;
  }
  sqlite3_finalize(stmt);
  return true;
}

/**
 * Изменение существующей записи в БД.
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

  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":SITE"), site, -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":PASSWORD"), pw, -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":CATEGORY"), cat, -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":COMMENT"), cmt, -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":ID"), id, -1, SQLITE_TRANSIENT);

    
  int rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    std::cerr << "error: " << sqlite3_errmsg(db_) << std::endl;
    return false;
  } else {
    std::cout << "data updated successfully" << std::endl;
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
  } else {
    std::cout << "data deleted successfully" << std::endl;
  }
  sqlite3_finalize(stmt);
  return true;
}

/**
 * Получение записей из БД: либо по поисковому запросу, либо по категории.
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
    std::cout << query;
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
      row.push_back(val);
    }
    results.push_back(row);
  }
  
  sqlite3_finalize(stmt);
  return results;
}
