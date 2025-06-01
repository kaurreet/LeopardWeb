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
	string add_course(string in_course_name, int in_CRN, string in_Department, string in_Instructor, string in_time, string in_Dofw, string in_Semester, int in_year, int in_credits);
	string remove_course(string in_course_name, int in_CRN, string in_Department, string in_Instructor, string in_time, string in_Dofw, string in_Semester, int in_year, int in_credits);
	string add_user(string in_user_add_f, string in_user_add_l, string in_user_add_ID, string in_user_add_Grad_year, string in_user_add_Major, string in_user_add_Email, int add_user_type, string user_add_Title, string user_add_YOH, string user_add_Department, string user_add_Office);
	string remove_user(string in_user_removef, string in_user_removel, string in_user_remove_ID, string in_user_remove_Grad_year, string in_user_remove_Major, string in_user_remove_Email, int remove_user_type, string user_remove_Title, string user_remove_YOH, string user_remove_Department, string user_remove_Office);
	void add_student_course(string in_student, string in_course);
	void remove_student_course(string in_student, string in_course);
	void search_roster(string in_course_search_roster);
	void print_roster(string in_course_print_roster);
	void search_courses(string in_course);
	string print_courses(string in_course);
	//destructor
	~Admin();

};

