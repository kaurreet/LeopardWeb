#pragma once
#include <iostream>
#include <string>
#include <set>
using std::string;

class User
{
	string first_name;
	string last_name;
	int ID;
public:
	//constructor
	User(string in_fname, string in_lname, int in_ID);
	//methods
	virtual string get_first_name();
	virtual string get_last_name();
	virtual int get_ID();
	virtual void print_all();
	//destructor
	~User();
};
