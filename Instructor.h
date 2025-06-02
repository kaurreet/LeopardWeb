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
	string ID;
	set<string> courses_taught;
public:
	//constructor
	Instructor();
	Instructor(string in_fname, string in_lname, string in_ID);
	//methods
	void show_first_name();
	void show_last_name();
	void show_all();
	void show_ID();
	void search_course(sqlite3* db, string course_add_drop, int Course_CRN, string department_course, string course_instructor, string course_start_time, string Meeting_times, string course_semester, int course_year, int course_credits);
	void print_class_list(string &student_query);
	string print_schedule();
	//destructor
	~Instructor();

};

