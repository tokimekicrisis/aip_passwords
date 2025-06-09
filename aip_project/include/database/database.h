#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

#include <vector>
#include <string>

class Database {
public:
  Database(const char* filename);
  ~Database();
  
  Database(const Database&) = delete;
  Database& operator=(const Database&) = delete;
  
  bool insertData(const char* site, const char* pw,
                  const char* cat, const char* cmt);

  bool deleteData(const char* id);

  bool updateData(const char* id,
                  const char* site, const char* pw,
                  const char* cat, const char* cmt);
  
  std::vector<std::vector<std::string>> extractData(const char* search_term,
                                                    const char* cat);
  
private:
  sqlite3* db_; 
};

#endif // DATABASE_H
