#pragma once
#include "Student.h"
#include <set>
extern "C" {
#include "sqlite3.h"
}
using std::set;
class Instructor :
    public Student
{
	string first_name;
	string last_name;
	int ID;
	string email;
	string title;
	int YOH;
	string department;
public:
	//constructor
	Instructor();
	Instructor(string in_fname, string in_lname, int in_ID);
	Instructor(string in_fname, string in_lname, int in_ID, string in_email, string in_title, int in_YOH, string in_department);
	//methods
	void set_email(string in_email);
	void set_title(string in_title);
	void set_YOH(int in_YOH);
	void set_Department(string in_department);
	string get_first_name();
	string get_last_name();
	string get_all();
	int get_ID();
	string get_title();
	int get_YOH();
	string get_Department();
	string search_course(sqlite3* db, string course_add_drop, int in_CRN, string in_dep, string in_instruct, string in_parameter);
	void print_class_list(string &student_query);
	string print_schedule(string in_fname, string in_lname);
	string get_studentname(int student_id);
	string getstudent_classlist(int in_student_id);
	string getcourse_roster(string title);
	string get_courseinfo(string title);
	//destructor
	~Instructor();

};

