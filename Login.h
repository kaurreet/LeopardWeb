#pragma once
#include <string>

extern "C" {
	#include "sqlite3.h"
}
using std::string;
class Login
{
	std::string username;
	std::string password;
	int ID;

	std::string authenticate();

public:
	Login(const std::string& uname, const std::string& pass, int ID);
	void loginUser(); 
	string getUsername();
	string getPassword();
	int getID();
	void loginUser(string in_username, string in_password, int ID);
};



//constructor username pass 
//ID number 

//use the get functins in user get first name, get last name and ID 