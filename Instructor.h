#pragma once
#include "Student.h"
class Instructor :
    public User
{
	string first_name;
	string last_name;
	string ID;
public:
	//constructor
	Instructor();
	Instructor(string in_fname, string in_lname, string in_ID);
	//methods
	void show_first_name();
	void show_last_name();
	void show_all();
	void show_ID();
	void search_course(string in_course);
	void print_class_list(string in_course);
	void print_schedule();
	//destructor
	~Instructor();

};

