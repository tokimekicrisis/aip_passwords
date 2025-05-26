#include "database/database.h"

#include "sqlite3.h"

#include <iostream>

Database::Database(const char* filename) {
  if (sqlite3_open(filename, &db_) != SQLITE_OK) {
    std::cerr << sqlite3_errmsg(db_) << std::endl;
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

Database::~Database() {
  sqlite3_close(db_);
}

bool Database::InsertData(const char* site, const char* pw, const char* cat, const char* cmt) {
  sqlite3_stmt* stmt;
  const char* query = "INSERT INTO PASSWORDS (SITE, PASSWORD, CATEGORY, COMMENT)"
                      "VALUES (:SITE, :PASSWORD, :CATEGORY, :COMMENT);";
  
  if (sqlite3_prepare_v2(db_, query, -1, &stmt, nullptr) != SQLITE_OK) {
    return false;
  }

  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":SITE"), site, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":PASSWORD"), pw, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":CATEGORY"), cat, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":COMMENT"), cmt, -1, SQLITE_STATIC);
  
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

// bool Database::ExtractData(const char* column, const char* data) {
//     sqlite3_stmt* stmt;
//     const char* query = "SELECT * FROM PASSWORDS WHERE ;";
    
//     if (sqlite3_prepare_v2(db_, query, -1, &stmt, nullptr) != SQLITE_OK) {
//         return false;
//     }

//     int rc = sqlite3_step(stmt);
//     if (rc != SQLITE_DONE) {
//         std::cerr << "error: " << sqlite3_errmsg(db_) << std::endl;
//         return false;
//     } else {
//         std::cout << "data extracted successfully" << std::endl;
//     }
//     sqlite3_finalize(stmt);
//     return true;
// }