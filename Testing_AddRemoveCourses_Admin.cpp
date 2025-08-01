#include <gtest/gtest.h>
#include "Admin.h"
#include "sqlite3.h"
#include <iostream>

//TEST1 for add_course 
TEST(AdminTest, AddCourse1) {
    sqlite3* db = nullptr;
    const char* dbPath = "assignment3 (1).db";
    int result = sqlite3_open(dbPath, &db);
    ASSERT_EQ(result, SQLITE_OK) << "Failed to open DB: " << sqlite3_errmsg(db);
    if (result != SQLITE_OK) {
        std::cerr << "Could not open database: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        std::cout << "Database opened successfully." << std::endl;
    }
    Admin admin("Unit", "Tester", 7777);
    int testCRN = 99999;
    std::string insertSQL = admin.add_course(
        "UnitTestCourse", testCRN, "TEST", "test_instructor", "3PM", "TR", "Spring", 2026, 5);
    char* errMsg = nullptr;
    result = sqlite3_exec(db, insertSQL.c_str(), nullptr, nullptr, &errMsg);
    EXPECT_EQ(result, SQLITE_OK) << "SQL execution failed: " << (errMsg ? errMsg : "unknown error");
    std::string cleanupSQL = "DELETE FROM COURSE WHERE CRN = " + std::to_string(testCRN) + ";";
    std::cout << "[SQL EXECUTED]: " << cleanupSQL << std::endl;
    sqlite3_exec(db, cleanupSQL.c_str(), nullptr, nullptr, nullptr);
    sqlite3_close(db);
}

//TEST2 for add course with duplicate CRN
TEST(AdminTest, AddCourse2) {
    sqlite3* db = nullptr;
    const char* dbPath = "assignment3 (1).db";
    int result = sqlite3_open(dbPath, &db);
    ASSERT_EQ(result, SQLITE_OK) << "Failed to open DB: " << sqlite3_errmsg(db);
    Admin admin("Unit", "Tester2", 8888);
    int testCRN = 50001;
    std::string insertSQL = admin.add_course(
        "UnitTestCourse", testCRN, "TEST", "test_instructor", "6PM", "WTR", "Fall", 2025, 4);
    char* errMsg = nullptr;
    result = sqlite3_exec(db, insertSQL.c_str(), nullptr, nullptr, &errMsg);
    EXPECT_NE(result, SQLITE_OK) << "SQL error while adding course: UNIQUE constraint failed: COURSE.CRN" << (errMsg ? errMsg : "unknown error");
    sqlite3_close(db);
}

// TEST3 Remove by all parameters
TEST(AdminTest, RemoveCourse1) {
    sqlite3* db = nullptr;
    const char* dbPath = "assignment3 (1).db";
    int result = sqlite3_open(dbPath, &db);
    ASSERT_EQ(result, SQLITE_OK) << "Failed to open DB: " << sqlite3_errmsg(db);

    Admin admin("Unit", "Tester", 7777);
    int testCRN = 98765;
    std::string insertSQL = admin.add_course(
        "ToRemove", testCRN, "TEST", "Temp Instructor", "4PM", "MW", "Spring", 2026, 4);
    char* errMsg = nullptr;
    result = sqlite3_exec(db, insertSQL.c_str(), nullptr, nullptr, &errMsg);
    ASSERT_EQ(result, SQLITE_OK) << "Failed to insert test course: " << (errMsg ? errMsg : "unknown error");
    std::string removeSQL = admin.remove_course(
        "ToRemove", testCRN, "TEST", "Temp Instructor", "4PM", "MW", "Spring", 2026, 4);
    std::cout << "[Executing] " << removeSQL << std::endl;
    result = sqlite3_exec(db, removeSQL.c_str(), nullptr, nullptr, &errMsg);
    EXPECT_EQ(result, SQLITE_OK) << "Failed to remove course: " << (errMsg ? errMsg : "unknown error");
    std::string selectSQL = "SELECT * FROM COURSE WHERE CRN = " + std::to_string(testCRN) + ";";
    sqlite3_stmt* stmt;
    result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
    ASSERT_EQ(result, SQLITE_OK) << "Failed to prepare SELECT after delete";
    result = sqlite3_step(stmt);
    EXPECT_EQ(result, SQLITE_DONE) << "Course was not removed successfully";

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
// TEST4 Remove by CRN only
TEST(AdminTest, RemoveCourse2) {
    sqlite3* db = nullptr;
    const char* dbPath = "assignment3 (1).db";
    int result = sqlite3_open(dbPath, &db);
    ASSERT_EQ(result, SQLITE_OK) << "Failed to open DB: " << sqlite3_errmsg(db);
    Admin admin("Unit", "Tester", 7777);
    int testCRN = 54321;
    std::string insertSQL = admin.add_course(
        "CRNTestCourse", testCRN, "TEST", "crn_tester", "1PM", "MW", "Fall", 2025, 3);
    char* errMsg = nullptr;
    result = sqlite3_exec(db, insertSQL.c_str(), nullptr, nullptr, &errMsg);
    ASSERT_EQ(result, SQLITE_OK) << "Insert failed before delete: " << (errMsg ? errMsg : "unknown");

    std::string deleteSQL = "DELETE FROM COURSE WHERE CRN = " + std::to_string(testCRN) + ";";
    std::cout << "[Executing] " << deleteSQL << std::endl;
    result = sqlite3_exec(db, deleteSQL.c_str(), nullptr, nullptr, &errMsg);
    EXPECT_EQ(result, SQLITE_OK) << "CRN-only delete failed: " << (errMsg ? errMsg : "unknown");

    std::string checkSQL = "SELECT * FROM COURSE WHERE CRN = " + std::to_string(testCRN) + ";";
    sqlite3_stmt* stmt;
    result = sqlite3_prepare_v2(db, checkSQL.c_str(), -1, &stmt, nullptr);
    ASSERT_EQ(result, SQLITE_OK);
    result = sqlite3_step(stmt);
    EXPECT_EQ(result, SQLITE_DONE) << "Course with CRN still exists after delete";
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


