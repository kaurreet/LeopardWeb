#include <gtest/gtest.h>
#include "Admin.h"
#include "sqlite3.h"
#include <iostream> 

//Test for add_course 
//Test add CalcA
TEST(AdminCourseTests, AddCourse1) {
    Admin admin("Test", "Admin", 0);  // dummy values for constructor

    std::string expected = "INSERT INTO COURSE VALUES(50000, 'CalcA', 'Math', 'Joe Cotton', '10:00 AM', 'MWF', 'Fall', 2025, 3);";
    std::string actual = admin.add_course("CalcA", 50000, "Math", "Joe Cotton", "10:00 AM", "MWF", "Fall", 2025, 3);

    EXPECT_EQ(actual, expected);
}
//Test for add_course
//Test add DifferentialEquations
TEST(AdminCourseTests, AddCourse2) {
    Admin admin("Test", "Admin", 0);  // dummy values for constructor

    std::string expected = "INSERT INTO COURSE VALUES(50012, 'DifferentialEquations', 'Math', 'Melfi Farrel', '8:00 AM', 'WF', 'Spring', 2024, 4);";
	std::string actual = admin.add_course("DifferentialEquations", 50012, "Math", "Melfi Farrel", "8:00 AM", "WF", "Spring", 2024, 4);
    
    EXPECT_EQ(actual, expected);
}

//Test for remove_course
//Test remove History
TEST(AdminCourseTests, RemoveCourse1) {
    Admin admin("Test", "Admin", 0);

    std::string expected = "DELETE FROM COURSE WHERE CRN = 50001 AND TITLE = 'History' AND DEPARTMENT = 'HUMN' AND INSTRUCTOR = 'Will Smith' AND TIME = '8:00 AM' AND Doftw = 'MWF' AND SEMESTER = 'Fall' AND YEAR = 2025 AND CREDITS = 3;";
    std::string actual = admin.remove_course("History", 50001, "HUMN", "Will Smith", "8:00 AM", "MWF", "Fall", 2025, 3);

    EXPECT_EQ(actual, expected);
}
//Test for remove_course
//Test remove Economics
TEST(AdminCourseTests, RemoveCourse2) {
    Admin admin("Test", "Admin", 0);

    std::string expected = "DELETE FROM COURSE WHERE CRN = 50200 AND TITLE = 'Economics' AND DEPARTMENT = 'HUMN' AND INSTRUCTOR = 'Allison Lance' AND TIME = '11:00 AM' AND Doftw = 'TTH' AND SEMESTER = 'Spring' AND YEAR = 2022 AND CREDITS = 4;";
	std::string actual = admin.remove_course("Economics", 50200, "HUMN", "Allison Lance", "11:00 AM", "TTH", "Spring", 2022, 4);

    EXPECT_EQ(actual, expected);
}
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

