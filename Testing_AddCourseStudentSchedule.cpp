#include <gtest/gtest.h>
#include "Student.h"
#include "sqlite3.h"
#include <iostream> 

//Add Course 1 to Student's schedule
TEST(StudentTest, AddCourse1) {
    sqlite3* db = nullptr;
    const char* dbPath = "assignment3 (1).db";
    ASSERT_EQ(sqlite3_open(dbPath, &db), SQLITE_OK);

    Student student("Unit", "TestStudent", 13580);
    std::string courseName = "AmericanHistory";

    // Ensure course exists in COURSE table
    std::string courseSQL = "INSERT INTO COURSE (CRN, TITLE, DEPARTMENT, INSTRUCTOR, TIME, DoftW, SEMESTER, YEAR, CREDITS) "
        "VALUES (11110, '" + courseName + "', 'Humanities', 'TestInstructor', '10AM', 'TR', 'Fall', 2025, 3);";
    sqlite3_exec(db, courseSQL.c_str(), nullptr, nullptr, nullptr);

    // Add course to REGISTERED
    std::string addSQL = student.add_course(db, courseName, student.get_ID());
    char* errMsg = nullptr;
    int result = sqlite3_exec(db, addSQL.c_str(), nullptr, nullptr, &errMsg);
    EXPECT_EQ(result, SQLITE_OK) << "Failed to add course: " << (errMsg ? errMsg : "unknown");

    // Verify insert
    std::string checkSQL = "SELECT * FROM REGISTERED WHERE TITLE = '" + courseName + "' AND StudentID = " + std::to_string(student.get_ID()) + ";";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, checkSQL.c_str(), -1, &stmt, nullptr);
    EXPECT_EQ(sqlite3_step(stmt), SQLITE_ROW) << "Course not added to student schedule";
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
//Add Course 2 by using course CRN 
TEST(StudentTest, AddCourse2) {
    sqlite3* db = nullptr;
    const char* dbPath = "assignment3 (1).db";
    ASSERT_EQ(sqlite3_open(dbPath, &db), SQLITE_OK);

    Student student("Unit", "TestStudent", 54323); 
	int crn = 50012;  // CRN for Computer Networks
    std::string courseName;

    std::string querySQL = "SELECT TITLE FROM COURSE WHERE CRN = " + std::to_string(crn) + ";";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, querySQL.c_str(), -1, &stmt, nullptr);
    ASSERT_EQ(rc, SQLITE_OK) << "Failed to prepare CRN lookup";

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        courseName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }
    else {
        FAIL() << "CRN not found in COURSE table";
    }
    sqlite3_finalize(stmt);

    //Course under the REGISTERED table using the title from the matching CRN
    std::string addSQL = student.add_course(db, courseName, student.get_ID());
    char* errMsg = nullptr;
    int result = sqlite3_exec(db, addSQL.c_str(), nullptr, nullptr, &errMsg);
    EXPECT_EQ(result, SQLITE_OK) << "Failed to register using CRN: " << (errMsg ? errMsg : "unknown");

    std::string checkSQL = "SELECT * FROM REGISTERED WHERE CRN = " + std::to_string(crn) + " AND StudentID = " + std::to_string(student.get_ID()) + ";";
    rc = sqlite3_prepare_v2(db, checkSQL.c_str(), -1, &stmt, nullptr);
    ASSERT_EQ(rc, SQLITE_OK);
    EXPECT_EQ(sqlite3_step(stmt), SQLITE_ROW) << "Course not added to schedule via CRN lookup";
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}