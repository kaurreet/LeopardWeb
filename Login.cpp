#include "Login.h"
#include <iostream>
using std::string;
#include <algorithm>

extern "C" {
	#include "sqlite3.h"
}

using std::cin;
using std::cout;
using std::endl;
using std::string;

Login::Login() {

}

Login::Login(const std::string& uname, const std::string& pass, int in_ID) {
	username = uname;
	password = pass;
	ID = in_ID;
}

string Login::getUsername() {
	return username;
}
string Login::getPassword() {
	return password;
}
int Login::getID() {
	return ID;
}
string Login::getRole(){
	return role;
}

void Login::setUsername(string in_user){
	username = in_user;
}
void Login::setPassword(string in_password){
	password = in_password;
}
void Login::setID(int in_ID){
	ID = in_ID;
}
void Login::setRole(string in_role){
	role = in_role;
}
void Login::logout(){
	username = "";
	password = "";
	ID = 0;
	role = "";
}


string Login::authenticate() {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc = sqlite3_open("assignment3.db", &db);

	if (rc != SQLITE_OK) {
		std::cout << "Error opening database.\n";
		return "invalid";
	}

	std::string query = "SELECT * FROM LOGINS WHERE Username=? AND Password=? AND ID=?;";
	rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

	if (rc == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 3, ID);
	}

	rc = sqlite3_step(stmt);
	std::string result = (rc == SQLITE_ROW) ? "valid" : "invalid";

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return result;
}

void Login::loginUser(string in_username, string in_password, int ID) {
	username = in_username;
	password = in_password;
	ID = ID;

	std::string status = authenticate();
	//use getUsername() and getPassword() functions inside of loginUser() --> loginUser(LoginSys.getUsername(), LoginSys.getPassword(), LgoinSys.getID()); <<in the main file Assignment_1>>
	if (status == "valid") {
		//implement SQL code to compare user input of username and pw with the database.
		sqlite3* db;
		sqlite3_stmt* stmt;
		int rc = sqlite3_open("assignment3.db", &db);
		std::cout << "Login successful.\n";

		if (rc != SQLITE_OK) {
			std::cout << "Error opening database.\n";
			return;
		}
		std::string query = "SELECT FirstName, LastName FROM users WHERE Username=? AND Password=? AND ID=?;"; 
		rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr); 

		if (rc == SQLITE_OK) {
			sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
			sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
			sqlite3_bind_int(stmt, 3, ID);

			rc = sqlite3_step(stmt);
			if (rc == SQLITE_ROW) {
				std::string first = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
				std::string last = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
				std::cout << "Login successful. Welcome, " << first << " " << last << "!\n";
			}
		}
		sqlite3_finalize(stmt);
		sqlite3_close(db);
	}
	else {
		std::cout << "Login failed. Try again.\n";
	}
}   

void Login::registerUser(string in_user, string in_pw, int in_ID, string in_role) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc = sqlite3_open("assignment3.db", &db);

	if (rc != SQLITE_OK) {
		cout << "Error opening database.\n";
		return;
	}

	string insert_query = "INSERT INTO LOGINS (Username, Password, ID, ROLE) VALUES (?, ?, ?, ?);";
	rc = sqlite3_prepare_v2(db, insert_query.c_str(), -1, &stmt, nullptr);

	if (rc == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, in_user.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, in_pw.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 3, in_ID);
		sqlite3_bind_text(stmt, 4, in_role.c_str(), -1, SQLITE_STATIC);

		rc = sqlite3_step(stmt);
		if (rc == SQLITE_DONE) {
			cout << "Registration successful. You can now log in.\n";
		}
		else {
			cout << "Registration failed.\n";
		}
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}
