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
	string first_name;
	string last_name;
	int ID;
	set<string> courses_taught;
public:
	//constructor
	Instructor(string in_fname, string in_lname, int in_ID);
	//methods
	string get_first_name();
	string get_last_name();
	string get_all();
	int get_ID();
	string search_course(sqlite3* db, string course_add_drop, int in_CRN, string in_dep, string in_instruct, string in_parameter);
	void print_class_list(string &student_query);
	string print_schedule(string in_fname, string in_lname);
	//destructor
	~Instructor();

};

