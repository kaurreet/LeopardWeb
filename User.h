#pragma once
#include <iostream>
#include <string>
using std::string;

class User
{
	string first_name;
	string last_name;
	string ID;

public:
	//constructor
	User();
	User(string in_fname, string in_lname, string in_ID);
	//methods
	virtual void show_first_name();
	virtual void show_last_name();
	virtual void show_ID();
	virtual void show_all();
	//destructor
	~User();
};