#include <gtest/gtest.h>
#include "Instructor.h"
#include "sqlite3.h"
#include <iostream> 

//Classlist for Microcontrollers
TEST(InstructorTest, DisplayClassRoster1) {
    sqlite3* db;
    ASSERT_EQ(sqlite3_open("assignment3 (1).db", &db), SQLITE_OK);

    std::string courseTitle = "Microcontrollers";
    sqlite3_stmt* stmt;

    std::string query = "SELECT StudentID FROM REGISTERED WHERE TITLE = ?;";
    bool studentFound = false;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, courseTitle.c_str(), -1, SQLITE_STATIC);

        std::cout << "Students registered in " << courseTitle << ":\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int studentID = sqlite3_column_int(stmt, 0);
            std::cout << "Student ID: " << studentID << "\n";
            studentFound = true;
        }

        sqlite3_finalize(stmt);
    }
    else {
        std::cerr << "Failed to prepare query.\n";
    }
    EXPECT_TRUE(studentFound) << "No students found for course: " << courseTitle;
    sqlite3_close(db);
}

//Classlist for AmericanHistory
TEST(InstructorTest, DisplayClassRoster2) {
    sqlite3* db;
    ASSERT_EQ(sqlite3_open("assignment3 (1).db", &db), SQLITE_OK);

    std::string courseTitle = "AmericanHistory";
    sqlite3_stmt* stmt;

    std::string query = "SELECT StudentID FROM REGISTERED WHERE TITLE = ?;";
    bool studentFound = false;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, courseTitle.c_str(), -1, SQLITE_STATIC);

        std::cout << "Students registered in " << courseTitle << ":\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int studentID = sqlite3_column_int(stmt, 0);
            std::cout << "Student ID: " << studentID << "\n";
            studentFound = true;
        }

        sqlite3_finalize(stmt);
    }
    else {
        std::cerr << "Failed to prepare query.\n";
    }
    EXPECT_TRUE(studentFound) << "No students found for course: " << courseTitle;
    sqlite3_close(db);
}


int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}