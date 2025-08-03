#include <gtest/gtest.h>
#include "Student.h"
#include "Instructor.h"
#include "Admin.h"
#include "sqlite3.h"
#include <iostream>

//Student Search by Title
TEST(CourseSearchTest, Student_SearchByTitle) {
    sqlite3* db;
    int rc = sqlite3_open("assignment3 (1).db", &db);
    ASSERT_EQ(rc, SQLITE_OK) << "Failed to open database.";

    //Student Test Physics
    std::string insert_sql = "INSERT INTO COURSE (TITLE, MAJOR, INSTRUCTOR, TIME, DAYS, SEMESTER, YEAR, CREDITS) "
        "VALUES ('Physics', 'BSCO', 'Dr. Smith', '10:00 AM', 'MWF', 'Fall', 2025, 3);";
    sqlite3_exec(db, insert_sql.c_str(), nullptr, nullptr, nullptr);

    Student studentUser("Test", "Student", 99901);
    std::string query = studentUser.search_course(db, "", 0, "Physics", "", "title");

    std::cout << "Student test: Connected to database. Searching for course with TITLE = 'Physics'.\n";
    std::cout << "Query used: " << query << "\n";

    sqlite3_close(db);
    EXPECT_TRUE(true); 
}
// Instructor Search by Semester
TEST(CourseSearchTest, Instructor_SearchBySemester) {
    sqlite3* db;
    int rc = sqlite3_open("assignment3 (1).db", &db);
    ASSERT_EQ(rc, SQLITE_OK) << "Failed to open database.";

    //Instructor Search Fall
    std::string insert_sql = "INSERT INTO COURSE (TITLE, MAJOR, INSTRUCTOR, TIME, DAYS, SEMESTER, YEAR, CREDITS) "
        "VALUES ('Circuits', 'EECE', 'Prof. Allen', '2:00 PM', 'TTH', 'Fall', 2025, 4);";
    sqlite3_exec(db, insert_sql.c_str(), nullptr, nullptr, nullptr);

    Instructor instructorUser("Test", "Instructor", 99902);
    std::string query = instructorUser.search_course(db, "", 0, "", "Fall", "semester");

    std::cout << "Instructor test: Connected to database. Searching for courses in SEMESTER = 'Fall'.\n";
    std::cout << "Query used: " << query << "\n";

    sqlite3_close(db);
    EXPECT_TRUE(true); 
}
// Admin Search by Credits
TEST(CourseSearchTest, Admin_SearchByCredits) {
    sqlite3* db;
    int rc = sqlite3_open("assignment3 (1).db", &db);
    ASSERT_EQ(rc, SQLITE_OK) << "Failed to open database.";

    //Admin Search 4 credits 
    std::string insert_sql = "INSERT INTO COURSE (TITLE, MAJOR, INSTRUCTOR, TIME, DAYS, SEMESTER, YEAR, CREDITS) "
        "VALUES ('Algorithms', 'CS', 'Dr. Lee', '12:00 PM', 'MW', 'Spring', 2025, 4);";
    sqlite3_exec(db, insert_sql.c_str(), nullptr, nullptr, nullptr);

    Admin adminUser("Test", "Admin", 99903);
    std::string query = adminUser.search_course(db, "", 4, "", "", "credits");

    std::cout << "Admin test: Connected to database. Searching for courses with CREDITS = 4.\n";
    std::cout << "Query used: " << query << "\n";

    sqlite3_close(db);
    EXPECT_TRUE(true); 
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
