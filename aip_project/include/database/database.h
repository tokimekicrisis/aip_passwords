#pragma once

#include <sqlite3.h>

#include <vector>
#include <string>

class Database {
public:
  Database(const char* filename);
  ~Database();
  
  Database(const Database&) = delete;
  Database& operator=(const Database&) = delete;
  
  bool InsertData(const char* site, const char* pw,
                  const char* cat, const char* cmt);

  bool DeleteData(const char* id);
  
  std::vector<std::vector<std::string>> ExtractData(const char* search_term, 
                                                    const char* cat);
  
private:
  sqlite3* db_; 
};