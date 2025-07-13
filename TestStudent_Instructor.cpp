
#include <gtest/gtest.h>
#include "Student.h"
#include "Instructor.h"

// ---------- Student Tests ----------
class StudentTest : public ::testing::Test {
protected:
    Student student;

    void SetUp() override {
        student = Student("Andy", "Le", 12345);
    }
};

TEST_F(StudentTest, AddCourseSQL) {
    std::string expected =
        "INSERT INTO REGISTERED (CRN, TITLE, DEPARTMENT, TIME, doftw, SEMESTER, YEAR, CREDITS, StudentID)"
        "SELECT CRN, TITLE, DEPARTMENT, TIME, DoftW, SEMESTER, YEAR, CREDITS, 12345 FROM COURSE WHERE TITLE = 'CS101';";
    EXPECT_EQ(student.add_course(nullptr, "CS101", 12345), expected);
}

TEST_F(StudentTest, RemoveCourseSQL) {
    std::string expected =
        "DELETE FROM REGISTERED WHERE TITLE = 'CS101' AND studentID = '12345';";
    EXPECT_EQ(student.remove_course(nullptr, "CS101", 12345), expected);
}

// ---------- Instructor Tests ----------
class InstructorTest : public ::testing::Test {
protected:
    Instructor instructor;

    void SetUp() override {
        instructor = Instructor("Dr", "Smith", 20001);
    }
};

TEST_F(InstructorTest, GetCourseRosterSQL) {
    std::string expected =
        "SELECT STUDENT.ID, STUDENT.NAME, STUDENT.SURNAME "
        "FROM STUDENT "
        "JOIN REGISTERED ON STUDENT.ID = REGISTERED.StudentID "
        "WHERE REGISTERED.TITLE = 'CS101';";
    EXPECT_EQ(instructor.getcourse_roster("CS101"), expected);
}
