#include "database/database.h"
#include <iostream>
#include <string>

std::string gen_password(const int len, const bool digits, const bool punct) {
    std::string characters =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    if (digits) {
        characters += "0123456789";
    }
    if (punct) {
        characters += "!@#$^&*()_-+=%:;/.,?";
    }

    std::string pw;
    pw.reserve(len);
    
    for (int i = 0; i < len; ++i) {
        pw += characters[rand() % (characters.length() - 1)];
    }
    
    return pw;
}


int main() {
        Database db("passwords.db");
        std::cout << "db open\n";

        // 2. Insert sample data
        bool insertSuccess = db.insert_data(
            "example.com", 
            "qwerty", 
            "social media", 
            "main acc"
        );

        if (!insertSuccess) {
            std::cerr << "failed to insert\n";
            return 1;
        }

        std::cout << "complete\n";

    return 0;
}