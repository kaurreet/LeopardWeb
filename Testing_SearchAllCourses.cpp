#include <gtest/gtest.h>
#include "Student.h"
#include "Instructor.h"
#include "Admin.h"
#include "sqlite3.h"
#include <iostream>

//Student Course Search
TEST(CourseSearchTest, Student_SearchCourses) {
    sqlite3* db;
    int rc = sqlite3_open("assignment3 (1).db", &db);
    ASSERT_EQ(rc, SQLITE_OK) << "Failed to open database.";

    Student studentUser("Test", "Student", 99901);
    std::string query = studentUser.search_course(db, "", 0, "", "", "no");
    EXPECT_EQ(query, "SELECT * FROM COURSE;");

    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    ASSERT_EQ(rc, SQLITE_OK);

    int row_count = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        row_count++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    EXPECT_GT(row_count, 0) << "No courses found (Student search).";
}

//Instructor Course Search
TEST(CourseSearchTest, Instructor_SearchCourses) {
    sqlite3* db;
    int rc = sqlite3_open("assignment3 (1).db", &db);
    ASSERT_EQ(rc, SQLITE_OK) << "Failed to open database.";

    Instructor instructorUser("Test", "Instructor", 99902);
    std::string query = instructorUser.search_course(db, "", 0, "", "", "no");
    EXPECT_EQ(query, "SELECT * FROM COURSE;");

    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    ASSERT_EQ(rc, SQLITE_OK);

    int row_count = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        row_count++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    EXPECT_GT(row_count, 0) << "No courses found (Instructor search).";
}

//Admin Course Search
TEST(CourseSearchTest, AdminSearch_Courses) {
    sqlite3* db;
    int rc = sqlite3_open("assignment3 (1).db", &db);
    ASSERT_EQ(rc, SQLITE_OK) << "Failed to open database.";

    Admin adminUser("Test", "Admin", 99903);
    std::string query = adminUser.search_course(db, "", 0, "", "", "no");
    EXPECT_EQ(query, "SELECT * FROM COURSE;");

    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    ASSERT_EQ(rc, SQLITE_OK);

    int row_count = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        row_count++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    EXPECT_GT(row_count, 0) << "No courses found (Admin search).";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



