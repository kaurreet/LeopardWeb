#pragma once
#include "User.h"
#include <set>
extern "C" {
#include "sqlite3.h"
}

using std::set;
class Student :
	public User
{
	string first_name;
	string last_name;
	int ID;
	string email;
	int gradYear;
	string major;
	//set<string> courses_enrolled;
public:
	//constructor
	Student();
	Student(string in_fname, string in_lname, int in_ID);
	Student(string in_fname, string in_lname, int in_ID, string in_email, int in_gradyear, string in_major);
	//methods
	void set_firstname(string in_fname);
	void set_lastname(string in_lname);
	void set_ID(int in_ID);
	void set_email(string in_email);
	void set_gradYear(int in_gradyear);
	void set_major(string in_major);

	string get_firstname();
	string get_lastname();
	int get_ID();
	string get_email();
	int get_gradYear();
	string get_major();

	string search_course(sqlite3* db, string course_add_drop, int in_CRN, string in_dep, string in_instruct, string in_parameter);
	string add_course(sqlite3* DB, string in_course_name, int ID);
	string remove_course(sqlite3* DB, string in_course_name, int ID);
	string print_schedule();
	//destructor
	~Student();
};
