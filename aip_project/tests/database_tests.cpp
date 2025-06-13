#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "database/database.h"

TEST_CASE("db init") {
    SUBCASE("first run") {
        Database db(":memory:");
        CHECK(db.isFirstRun() == true);
    }

    SUBCASE("master") {
        Database db(":memory:");
        CHECK(db.setMaster("1234") == true);
        CHECK(db.verifyMaster("1234") == true);
        CHECK(db.verifyMaster("4321") == false);
    }
}

TEST_CASE("db operations") {
    Database db(":memory:");
    db.setMaster("1234");

    SUBCASE("insert/extract") {
        CHECK(db.insertData("example.com", "qwerty", "aaa", "bbb") == true);

        auto results = db.extractData(nullptr, nullptr);
        CHECK(results.size() == 1);
        CHECK(results[0][1] == "example.com");
    }

    SUBCASE("update/delete") {
        db.insertData("site.com", "pass", "a", "");
        auto initial = db.extractData("site.com", nullptr);
        std::string id = initial[0][0];

        CHECK(db.updateData(id.c_str(), "newsite.com", "newpass", "b", "c") == true);
        CHECK(db.deleteData(id.c_str()) == true);
    }
}

TEST_CASE("encryption") {
    Database db(":memory:");
    db.setMaster("1234");

    std::string field = "abcde";
    CHECK(db.xorEncrypt(db.xorEncrypt(field)) == field);
}
