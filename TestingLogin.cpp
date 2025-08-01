#include <gtest/gtest.h>
#include "Login.h"
#include "sqlite3.h"
#include <iostream> 

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
//student test 2
TEST(LoginTest, Student2ValidLogin) {
	sqlite3* db;
	sqlite3_open("assignment3.db", &db);
	sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS LOGINS (Username TEXT, Password TEXT, ID INTEGER PRIMARY KEY, Role TEXT);", nullptr, nullptr, nullptr);
	sqlite3_close(db);
	//Login testLogin("test", "test", 00000);
	Login testLogin("pazfg", "wit3", 10005);
	EXPECT_EQ(testLogin.authenticate(), "invalid");
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
//Instructor test 2
TEST(LoginTest, Instructor2ValidLogin) {
	sqlite3* db;
	sqlite3_open("assignment3.db", &db);
	sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS LOGINS (Username TEXT, Password TEXT, ID INTEGER PRIMARY KEY, Role TEXT);", nullptr, nullptr, nullptr);
	sqlite3_close(db);
	//Login testLogin("test", "test", 00000);
	Login testLogin("avetaf", "prof1", 20001);
	EXPECT_EQ(testLogin.authenticate(), "valid");
} 

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}