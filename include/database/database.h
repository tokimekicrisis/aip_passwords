#include <sqlite3.h>

class Database {
public:
    Database(const char* filename);
    ~Database();
    
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
    
    bool insert_data(const char* site, const char* pw,
                    const char* cat, const char* cmt);
    
    bool extract_data(const char* column, const char* data);
    
private:
    sqlite3* db_; 
};