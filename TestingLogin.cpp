#include <gtest/gtest.h>
#include "Login.h"
#include "sqlite3.h"
#include <iostream> 

//Valid user&pass for all users
//student test 1
TEST(LoginTest, Student1ValidLogin) {
	sqlite3* db;
	sqlite3_open("assignment3.db", &db);
	sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS LOGINS (Username TEXT, Password TEXT, ID INTEGER PRIMARY KEY, Role TEXT);", nullptr, nullptr, nullptr);
	sqlite3_close(db);
	//Login testLogin("test", "test", 00000); 
	Login testLogin("kaurm", "leopard1", 10001);
	EXPECT_EQ(testLogin.authenticate(), "valid");
}
//Admin test 1
TEST(LoginTest, Admin1ValidLogin) {
	sqlite3* db;
	sqlite3_open("assignment3.db", &db);
	sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS LOGINS (Username TEXT, Password TEXT, ID INTEGER PRIMARY KEY, Role TEXT);", nullptr, nullptr, nullptr);
	sqlite3_close(db);
	//Login testLogin("test", "test", 00000);
	Login testLogin("dookharann", "admin1", 10100);
	EXPECT_EQ(testLogin.authenticate(), "valid");
}
//Instructor test 1
TEST(LoginTest, Instructor1ValidLogin) {
	sqlite3* db;
	sqlite3_open("assignment3.db", &db);
	sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS LOGINS (Username TEXT, Password TEXT, ID INTEGER PRIMARY KEY, Role TEXT);", nullptr, nullptr, nullptr);
	sqlite3_close(db);
	//Login testLogin("test", "test", 00000);
	Login testLogin("basnets", "professor10", 20010);
	EXPECT_EQ(testLogin.authenticate(), "valid");
}

// Valid username not valid password
TEST(LoginTest, InvalidPassword) {
	sqlite3* db;
	sqlite3_open("assignment3.db", &db);
	sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS LOGINS (Username TEXT, Password TEXT, ID INTEGER PRIMARY KEY, Role TEXT);", nullptr, nullptr, nullptr);
	sqlite3_close(db);
	//Login testLogin("test", "test", 00000);
	Login testLogin("kaurm", "wrongpassword", 10001);
	EXPECT_EQ(testLogin.authenticate(), "invalid");
}

// invalid username any password 
//student test 2
TEST(LoginTest, Student2InvalidUsername) {
	sqlite3* db;
	sqlite3_open("assignment3.db", &db);
	sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS LOGINS (Username TEXT, Password TEXT, ID INTEGER PRIMARY KEY, Role TEXT);", nullptr, nullptr, nullptr);
	sqlite3_close(db);
	//Login testLogin("test", "test", 00000);
	Login testLogin("pazfg", "wit3", 10005);
	EXPECT_EQ(testLogin.authenticate(), "invalid");
}
//admin test 2
TEST(LoginTest, Admin2ValidLogin) {
	sqlite3* db;
	sqlite3_open("assignment3.db", &db);
	sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS LOGINS (Username TEXT, Password TEXT, ID INTEGER PRIMARY KEY, Role TEXT);", nullptr, nullptr, nullptr);
	sqlite3_close(db);
	//Login testLogin("test", "test", 00000);
	Login testLogin("dookharannJK", "admin1", 10120);
	EXPECT_EQ(testLogin.authenticate(), "invalid");
}

// valid username no password 
//Instructor test 2
TEST(LoginTest, Instructor2ValidLogin) {
	sqlite3* db;
	sqlite3_open("assignment3.db", &db);
	sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS LOGINS (Username TEXT, Password TEXT, ID INTEGER PRIMARY KEY, Role TEXT);", nullptr, nullptr, nullptr);
	sqlite3_close(db);
	//Login testLogin("test", "test", 00000);
	Login testLogin("avetaf", " ", 20001);
	EXPECT_EQ(testLogin.authenticate(), "invalid");
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}