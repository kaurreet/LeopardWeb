#pragma once
#include "Student.h"
#include <set>
extern "C" {
#include "sqlite3.h"
}
using std::set;
class Instructor :
    public User
{
public:
	string first_name;
	string last_name;
	int ID;
	set<string> courses_taught;

	//constructor
	Instructor(string in_fname, string in_lname, int in_ID);
	//methods
	void show_first_name();
	void show_last_name();
	void show_all();
	void show_ID();
	string search_course(sqlite3* db, string course_add_drop, string in_fname, string in_lname);
	void print_class_list(string &student_query);
	string print_schedule(string in_fname, string in_lname);
	//destructor
	~Instructor();

};

