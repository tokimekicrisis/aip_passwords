#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

#include <QString>

#include <vector>
#include <string>

/**
 *Наша база данных. Работает на sqlite3.
 *Инициализуется с помощью пути к файлу.
 *Также содержит методы обработки главного пароля
 *и шифрования паролей в БД.
 */
class Database {
public:
  Database(const char* filename);
  ~Database();
  
  Database(const Database&) = delete;
  Database& operator=(const Database&) = delete;

  bool isFirstRun();
  bool setMaster(const QString& password);
  bool verifyMaster(const QString& password);
  std::string getMaster();
  
  bool insertData(const char* site, const char* pw,
                  const char* cat, const char* cmt);

  bool deleteData(const char* id);

  bool updateData(const char* id,
                  const char* site, const char* pw,
                  const char* cat, const char* cmt);
  
  std::vector<std::vector<std::string>> extractData(const char* search_term,
                                                    const char* cat);
    std::string xorEncrypt(const std::string& input);
  
private:
  sqlite3* db_;
  bool createMaster();
};

#endif // DATABASE_H
