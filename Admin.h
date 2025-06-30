#pragma once
#include "Instructor.h"
extern "C" {
#include "sqlite3.h"
}
class Admin :
    public User
{
	string first_name;
	string last_name;
	int ID;
	string email;
	string title;
	string office;
public:
	//constructor
	Admin(string in_fname, string in_lname, int in_ID);
	Admin(string in_fname, string in_lname, int in_ID, string in_email, string in_title, string in_office);
	//methods
	void show_all();
	void set_email(string in_email);
	void set_firstname(string in_fname);
	void set_lastname(string in_lname);
	void set_title(string in_title);
	void set_office(string in_office);

	string get_email();
	string get_firstname();
	string get_lastname();
	string get_title();
	string get_office();
	int get_ID();
	string add_course(string in_course_name, int in_CRN, string in_Department, string in_Instructor, string in_time, string in_Doftw, string in_Semester, int in_year, int in_credits);
	string remove_course(string in_course_name, int in_CRN, string in_Department, string in_Instructor, string in_time, string in_Doftw, string in_Semester, int in_year, int in_credits);
	string add_user(string in_user_add_f, string in_user_add_l, int in_user_add_ID, int in_user_add_Grad_year, string in_user_add_Major, string in_user_add_Email, int add_user_type, string user_add_Title, int user_add_YOH, string user_add_Department, string user_add_Office);
	string remove_user(string in_user_remove_f, string in_user_remove_l, int in_user_remove_ID, int in_user_remove_Grad_year, string in_user_remove_Major, string in_user_remove_Email, int remove_user_type, string user_remove_Title, int user_remove_YOH, string user_remove_Department, string user_remove_Office);
	string update_user(sqlite3* db, string user_searchf, string user_searchl, string user_search_ID, string user_search_Grad_year, string user_update_Grad_year, string user_search_Major, string user_update_major, string user_search_Email, int search_user_type, string user_search_Title, string user_update_Title, string user_search_YOH, string user_search_Department, string user_add_Office);
	void add_student_course(string in_student, string in_course);
	void remove_student_course(string in_student, string in_course);
	void search_roster(sqlite3* db, string user_searchf, string user_searchl, string user_search_ID, string user_search_Grad_year, string user_search_Major, string user_search_Email, string search_user_type, string user_search_Title, string user_search_YOH, string user_search_Department, string user_search_Office);
	void print_roster(string &student_query, string &instructor_query, string &admin_query);
	string search_course(sqlite3* db, string course_add_drop, int in_CRN, string in_dep, string in_instruct, string in_parameter);
	string print_courses(string in_course);
	//destructor
	~Admin();

};

