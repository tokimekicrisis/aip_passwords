#include "database/database.h"

#include <iostream>
#include <string>


std::string GenPassword(const int len, const bool digits, const bool punct) {
  std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
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

  bool success = db.InsertData(
      "example.com", 
      "qwerty", 
      "social media", 
      "main acc"
  );

  if (!success) {
    std::cerr << "failed to insert\n";
    return 1;
  }

  std::cout << "complete\n";

return 0;
}