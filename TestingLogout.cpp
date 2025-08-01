#include <gtest/gtest.h>
#include "Login.h"
#include "sqlite3.h"
#include <iostream> 

TEST(LoginTest, Logout1) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    std::string uname = "kaurm";
    std::string pwd = "leopard1";
    int id = 10001;
    bool found = false;
    if (sqlite3_open("assignment3 (1).db", &db) == SQLITE_OK) {
        std::string query = "SELECT * FROM LOGINS WHERE Username=? AND Password=? AND ID=?;";
        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, uname.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, pwd.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 3, id);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                found = true;
            }
            sqlite3_finalize(stmt);
        }
        sqlite3_close(db);
    }
    ASSERT_TRUE(found) << "Credentials not found in DB";
    Login user(uname, pwd, id);
    user.setRole("student");
    std::string result = user.logout();
    EXPECT_EQ(user.getUsername(), "");
    EXPECT_EQ(user.getPassword(), "");
    EXPECT_EQ(user.getID(), 0);
    EXPECT_EQ(user.getRole(), "");
    EXPECT_EQ(result, "Logged out successfully.");
}
TEST(LoginTest, Logout2) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    std::string uname = "kaurm";
    std::string pwd = "leopard1";
    int id = 10001;
    bool found = false;
    if (sqlite3_open("assignment3 (1).db", &db) == SQLITE_OK) {
        std::string query = "SELECT * FROM LOGINS WHERE Username=? AND Password=? AND ID=?;";
        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, uname.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, pwd.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 3, id);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                found = true;
            }
            sqlite3_finalize(stmt);
        }
        sqlite3_close(db);
    }
    ASSERT_TRUE(found) << "Credentials not found in DB";
    Login user(uname, pwd, id);
    user.setRole("student");
    // No logout call
    EXPECT_EQ(user.getUsername(), uname);
    EXPECT_EQ(user.getPassword(), pwd);
    EXPECT_EQ(user.getID(), id);
    EXPECT_EQ(user.getRole(), "student");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
