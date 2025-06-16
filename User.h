#pragma once
#include <iostream>
#include <string>
#include <set>
using std::string;

class User
{
public:
	string first_name;
	string last_name;
	int ID;

	//constructor
	User();
	User(string in_fname, string in_lname, int in_ID);
	//methods
	virtual string get_first_name(string in_first_name);
	virtual string get_last_name(string in_last_name);
	virtual int get_ID(int in_ID);
	virtual void print_all();
	//destructor
	~User();
};
