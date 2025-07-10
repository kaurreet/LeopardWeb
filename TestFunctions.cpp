#include "gtest/gtest.h"
#include "Admin.h"
#include "Login.h"

//Test for add_course 
TEST(AdminCourseTests, AddCourseReturnsCorrectSQL) {
	Admin admin("Test", "Admin", 0) //dummy values 

	std::string expected = "INSERT INTO COURSE VALUES(50000, 'CalcA', 'Math', 'Joe Cotton', '10:00 AM', 'MWF', 'Fall', 2025, 3);";
	std::string actual = admin.add_course("CalcA", 50000, "Math", "Joe Cotton", "10:00AM", 'MWF', "Fall", 2025, 3);

	EXPECT_EQ(actual, expected);
}

//Test for remove_course
TEST(AdminCourseTests, RemoveCourseReturnsCorrectSQL) {
	Admin admin("Test", "Admin", 0);

	std::string expected = "DELETE FROM COURSE WHERE CRN = 50001 AND TITLE = 'History' AND DEPARTMENT = 'HUMN' AND INSTRUCTOR = 'Will Smith' AND TIME = '8:00 AM' AND Doftw = 'MWF' AND SEMESTER = 'Fall' AND YEAR = 2025 AND CREDITS = 3;";
	std::string actual = admin.remove_course("History", 50001, "HUMN", "Will Smith", "8:00 AM", "MWF", "Fall", 2025, 3);
	EXPECT_EQ(actual, expected); 
}



//Fake Login class for testing purposes
class FakeLogin : public Login {
public:
		FakeLogin(const std::string& uname, const std::string& pass, int in_ID) : 
		Login(uname, pass, in_ID) {}

	std::string authenticate() override {
		if (getUsername() == "testuser" && getPassword() == "testpass" && getID() == 12345) {
			return "valid";
		}
		return "invalid";
	}
};
//Test for valid login 
TEST(LoginTest, ValidFakeLogin) {
	FakeLogin login("testuser", "testpass", 00000);
	EXPECT_EQ(login.authenticate(), "valid");
}
//Test for incorrect login
TEST(LoginTest, InvalidFakeLogin) {
	FakeLogin login("wronguser", "wrongpass", 99999);
	EXPECT_EQ(login.authenticate(), "invalid");
}