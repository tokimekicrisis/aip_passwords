#include "database/database.h"
#include "ui/main_window.h"
#include "ui_edit_pw.h"
#include "ui_add_pw.h"

#include <QApplication>

#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    // Database db("passwords.db");
    // std::cout << "db open\n";

    // bool success = db.InsertData(
    //     "example.com",
    //     "qwerty",
    //     "social media",
    //     "main acc"
    //     );

    // if (!success) {
    //     std::cerr << "failed to insert\n";
    //     return 1;
    // }

    // std::vector<std::vector<std::string>> result = db.ExtractData(nullptr, "social media");
    // std::vector<std::vector<std::string>> result2 = db.ExtractData("lol", nullptr);
    // std::vector<std::vector<std::string>> result3 = db.ExtractData(nullptr, nullptr);

    // bool dlt = db.DeleteData("1");
    // result3 = db.ExtractData(nullptr, nullptr);
    // for (const auto &inner_vec : result3) {
    //     for (const auto &elem : inner_vec) {
    //         std::cout << elem << " ";
    //     }
    //     std::cout << "\n";
    // }

    // std::cout << "complete\n";

    return a.exec();
}
