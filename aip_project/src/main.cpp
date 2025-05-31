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

  std::vector<std::vector<std::string>> result = db.ExtractData(nullptr, "social media");
  std::vector<std::vector<std::string>> result2 = db.ExtractData("lol", nullptr);
  std::vector<std::vector<std::string>> result3 = db.ExtractData(nullptr, nullptr);

  bool dlt = db.DeleteData("1");
  result3 = db.ExtractData(nullptr, nullptr);
      for (const auto &inner_vec : result3) {
        for (const auto &elem : inner_vec) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }
    
    return 0;

  std::cout << "complete\n";

return 0;
}