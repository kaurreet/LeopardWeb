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
	set<string> courses_enrolled;
public:
	//constructor
	Student(string in_fname, string in_lname, int in_ID);
	//methods
	string search_course(sqlite3* db, string course_add_drop, int in_CRN, string in_dep, string in_instruct, string in_parameter);
	string add_course(sqlite3* DB, string in_course_name, int ID);
	string remove_course(sqlite3* DB, string in_course_name, int ID);
	string print_schedule();
	//destructor
	~Student();
};
