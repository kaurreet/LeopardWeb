#include <gtest/gtest.h>
#include "Student.h"
#include "sqlite3.h"
#include <iostream> 

// RemoveCourse1: Remove course from student schedule using title "AmericanHistory"
TEST(StudentTest, RemoveCourse1) {
    sqlite3* db = nullptr;
    ASSERT_EQ(sqlite3_open("assignment3 (1).db", &db), SQLITE_OK);

    Student student("Unit", "TestStudent", 13580);
    std::string courseName = "AmericanHistory";  // Same course used in AddCourse1

    // Remove the course using title
    std::string removeSQL = student.remove_course(db, courseName, student.get_ID());
    char* errMsg = nullptr;
    int result = sqlite3_exec(db, removeSQL.c_str(), nullptr, nullptr, &errMsg);
    EXPECT_EQ(result, SQLITE_OK) << "Failed to remove course: " << (errMsg ? errMsg : "unknown");

    std::string checkSQL = "SELECT * FROM REGISTERED WHERE TITLE = '" + courseName + "' AND StudentID = " + std::to_string(student.get_ID()) + ";";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, checkSQL.c_str(), -1, &stmt, nullptr);
    EXPECT_EQ(sqlite3_step(stmt), SQLITE_DONE) << "Course still exists in schedule after removal";
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
// RemoveCourse2: Remove course from student schedule using CRN 50012 --> ComputerNetworks
TEST(StudentTest, RemoveCourse2) {
    sqlite3* db = nullptr;
    ASSERT_EQ(sqlite3_open("assignment3 (1).db", &db), SQLITE_OK);

    Student student("Unit", "TestStudent", 54323); 
    int crn = 50012;
    std::string courseTitle;

    std::string querySQL = "SELECT TITLE FROM COURSE WHERE CRN = " + std::to_string(crn) + ";";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, querySQL.c_str(), -1, &stmt, nullptr);
    ASSERT_EQ(rc, SQLITE_OK) << "Failed to lookup course title from CRN";

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        courseTitle = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }
    else {
        FAIL() << "Course with CRN not found in COURSE table";
    }
    sqlite3_finalize(stmt);
    std::string removeSQL = student.remove_course(db, courseTitle, student.get_ID());
    char* errMsg = nullptr;
    int result = sqlite3_exec(db, removeSQL.c_str(), nullptr, nullptr, &errMsg);
    EXPECT_EQ(result, SQLITE_OK) << "Failed to remove course by CRN: " << (errMsg ? errMsg : "unknown");
    std::string checkSQL = "SELECT * FROM REGISTERED WHERE CRN = " + std::to_string(crn) + " AND StudentID = " + std::to_string(student.get_ID()) + ";";
    rc = sqlite3_prepare_v2(db, checkSQL.c_str(), -1, &stmt, nullptr);
    ASSERT_EQ(rc, SQLITE_OK);
    EXPECT_EQ(sqlite3_step(stmt), SQLITE_DONE) << "Course still exists in REGISTERED after removal";
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}