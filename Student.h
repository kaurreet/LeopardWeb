#pragma once
#include "User.h"
class Student :
	public User
{
	string first_name;
	string last_name;
	string ID;
public:
	//constructor
	Student();
	Student(string in_fname, string in_lname, string in_ID);
	//methods
	void show_first_name();
	void show_last_name();
	void show_all();
	void show_ID();
	void search_course(string in_course);
	void add_drop_course(string in_course, string in_add_drop);
	void print_schedule();
	//destructor
	~Student();
};