#include <gtest/gtest.h>
#include "Student.h"
#include "Instructor.h"
#include "Admin.h"

// ---------- Student Search Tests ----------
class StudentSearchTest : public ::testing::Test {
protected:
    Student student;
    void SetUp() override {
        student = Student("Andy", "Le", 12345);
    }
};

TEST_F(StudentSearchTest, DefaultSearch) {
    std::string expected = "SELECT * FROM COURSE;";
    EXPECT_EQ(student.search_course(nullptr, "", 0, "", "", "no"), expected);
}

TEST_F(StudentSearchTest, SearchByName) {
    std::string expected = "SELECT * FROM COURSE WHERE TITLE = 'CS101';";
    EXPECT_EQ(student.search_course(nullptr, "CS101", 0, "", "", "name"), expected);
}

TEST_F(StudentSearchTest, SearchByCRN) {
    std::string expected = "SELECT * FROM COURSE WHERE CRN = 50001;";
    EXPECT_EQ(student.search_course(nullptr, "", 50001, "", "", "crn"), expected);
}

TEST_F(StudentSearchTest, SearchByDepartment) {
    std::string expected = "SELECT * FROM COURSE WHERE DEPARTMENT = 'CS';";
    EXPECT_EQ(student.search_course(nullptr, "CS", 0, "", "", "dep"), expected);
}

TEST_F(StudentSearchTest, SearchByInstructor) {
    std::string expected = "SELECT * FROM COURSE WHERE INSTRUCTOR = 'Dr. Smith';";
    EXPECT_EQ(student.search_course(nullptr, "", 0, "", "Dr. Smith", "instructor"), expected);
}

// ---------- Instructor Search Tests ----------
class InstructorSearchTest : public ::testing::Test {
protected:
    Instructor instructor;
    void SetUp() override {
        instructor = Instructor("David", "Smith", 20001);
    }
};

TEST_F(InstructorSearchTest, DefaultSearch) {
    std::string expected = "SELECT * FROM COURSE;";
    EXPECT_EQ(instructor.search_course(nullptr, "", 0, "", "", "no"), expected);
}

TEST_F(InstructorSearchTest, SearchByName) {
    std::string expected = "SELECT * FROM COURSE WHERE TITLE = 'CS101';";
    EXPECT_EQ(instructor.search_course(nullptr, "CS101", 0, "", "", "name"), expected);
}

TEST_F(InstructorSearchTest, SearchByCRN) {
    std::string expected = "SELECT * FROM COURSE WHERE CRN = 50001;";
    EXPECT_EQ(instructor.search_course(nullptr, "", 50001, "", "", "crn"), expected);
}

TEST_F(InstructorSearchTest, SearchByDepartment) {
    std::string expected = "SELECT * FROM COURSE WHERE DEPARTMENT = 'CS';";
    EXPECT_EQ(instructor.search_course(nullptr, "CS", 0, "", "", "dep"), expected);
}

TEST_F(InstructorSearchTest, SearchByInstructor) {
    std::string expected = "SELECT * FROM COURSE WHERE INSTRUCTOR = 'Dr. Smith';";
    EXPECT_EQ(instructor.search_course(nullptr, "", 0, "", "Dr. Smith", "instructor"), expected);
}

// ---------- Admin Search Tests ----------
class AdminSearchTest : public ::testing::Test {
protected:
    Admin admin;
    void SetUp() override {
        admin = Admin("Admin", "User", 99999);
    }
};

TEST_F(AdminSearchTest, DefaultSearch) {
    std::string expected = "SELECT * FROM COURSE;";
    EXPECT_EQ(admin.search_course(nullptr, "", 0, "", "", "no"), expected);
}

TEST_F(AdminSearchTest, SearchByName) {
    std::string expected = "SELECT * FROM COURSE WHERE TITLE = 'CS101';";
    EXPECT_EQ(admin.search_course(nullptr, "CS101", 0, "", "", "name"), expected);
}

TEST_F(AdminSearchTest, SearchByCRN) {
    std::string expected = "SELECT * FROM COURSE WHERE CRN = 50001;";
    EXPECT_EQ(admin.search_course(nullptr, "", 50001, "", "", "crn"), expected);
}

TEST_F(AdminSearchTest, SearchByDepartment) {
    std::string expected = "SELECT * FROM COURSE WHERE DEPARTMENT = 'CS';";
    EXPECT_EQ(admin.search_course(nullptr, "CS", 0, "", "", "dep"), expected);
}

TEST_F(AdminSearchTest, SearchByInstructor) {
    std::string expected = "SELECT * FROM COURSE WHERE INSTRUCTOR = 'Dr. Smith';";
    EXPECT_EQ(admin.search_course(nullptr, "", 0, "", "Dr. Smith", "instructor"), expected);
}
