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
	string role;
public:
	Login();
	string authenticate();
	Login(const std::string& uname, const std::string& pass, int in_ID);
	void loginUser();
	void loginUser(string in_username, string in_password, int ID);
	string getUsername();
	string getPassword();
	int getID();
	string getRole();

	void setUsername(string in_user);
	void setPassword(string in_password);
	void setID(int in_ID);
	void setRole(string in_role);

	void registerUser(string in_user, string in_pw, int in_ID, string in_role);


	//Logout function
	void logout();
};



//constructor username pass 
//ID number 

//use the get functins in user get first name, get last name and ID 
