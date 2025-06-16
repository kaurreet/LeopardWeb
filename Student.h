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
public:
	string first_name;
	string last_name;
	int ID;
	set<string> courses_enrolled;

	//constructor
	Student(string in_fname, string in_lname, int in_ID);
	//methods
	void search_course(sqlite3* db, string course_add_drop, int Course_CRN, string department_course, string course_instructor, string course_start_time, string Meeting_times, string course_semester, int course_year, int course_credits);
	string add_course(sqlite3* DB, string in_course_name, int ID);
	string remove_course(sqlite3* DB, string in_course_name, int ID);
	string print_schedule();
	//destructor
	~Student();
};
