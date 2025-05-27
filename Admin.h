#pragma once
#include "Instructor.h"
class Admin :
    public User
{
	string first_name;
	string last_name;
	string ID;
public:
	//constructor
	Admin();
	Admin(string in_fname, string in_lname, string in_ID);
	//methods
	void show_first_name();
	void show_last_name();
	void show_all();
	void show_ID();
	void add_course(string in_course);
	void remove_course(string in_course);
	void add_user(string in_user);
	void remove_user(string in_user);
	void add_student_course(string in_student, string in_course);
	void remove_student_course(string in_student, string in_course);
	void search_roster(string in_course_search_roster);
	void print_roster(string in_course_print_roster);
	void search_courses(string in_course);
	void print_courses(string in_course);
	//destructor
	~Admin();

};

