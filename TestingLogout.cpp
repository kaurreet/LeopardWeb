#include <gtest/gtest.h>
#include "Login.h"
#include "sqlite3.h"
#include <iostream> 

//student kaurm logs out 
TEST(LoginTest, LogoutUser) {
    Login testLogin("kaurm", "leopard1", 10001);
    testLogin.setRole("student");

    testLogin.logout();

    EXPECT_EQ(testLogin.getUsername(), "");
    EXPECT_EQ(testLogin.getPassword(), "");
    EXPECT_EQ(testLogin.getID(), 0);
    EXPECT_EQ(testLogin.getRole(), "");
}

//Instructor elsadhi logs out
TEST(LoginTest, LogoutUser2) {
    Login testLogin("elsadih", "professor7", 20007);
	testLogin.setRole("instructor");    

    testLogin.logout();
    EXPECT_EQ(testLogin.getUsername(), "");
    EXPECT_EQ(testLogin.getPassword(), "");
    EXPECT_EQ(testLogin.getID(), 0);
	EXPECT_EQ(testLogin.getRole(), "");
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

