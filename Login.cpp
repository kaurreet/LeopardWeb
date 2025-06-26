#include "Login.h"
#include <iostream>
using std::string;

extern "C" {
	#include "sqlite3.h"
}

Login::Login(const std::string& uname, const std::string& pass, int ID) {
	username = uname;
	password = pass;
	ID = ID;
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

std::string Login::authenticate() {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc = sqlite3_open("assignment3.db", &db);

	if (rc != SQLITE_OK) {
		std::cout << "Error opening database.\n";
		return "invalid";
	}

	std::string query = "SELECT * FROM users WHERE Username=? AND Password=? AND ID=?;";
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

