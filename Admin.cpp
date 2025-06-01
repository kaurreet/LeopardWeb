#include "Admin.h"
#include <iostream>
#include <algorithm>
#include "sqlite3.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
Admin::Admin() {
	first_name = "Andy";
	last_name = "Le";
}
Admin::Admin(string in_fname, string in_lname, string in_ID) {
	first_name = in_fname;
	last_name = in_lname;
	ID = in_ID;
}
void Admin::show_first_name() {
	cout << first_name << endl;
}
void Admin::show_last_name() {
	cout << last_name << endl;
}
void Admin::show_all() {
	cout << first_name << endl;
	cout << last_name << endl;
	cout << ID << endl;
}
void Admin::show_ID() {
	cout << ID << endl;
}
string Admin::add_course(string in_course_name, int in_CRN, string in_Department, string in_Instructor, string in_time, string in_Doftw, string in_Semester, int in_year, int in_credits) {
	//cout << "Course Added!";
	return "INSERT INTO COURSE VALUES(" + std::to_string(in_CRN) + ", '" + in_course_name + "', '" + in_Department + "', '" + in_Instructor + "', '" + in_time + "', '" + in_Doftw + "', '" + in_Semester + "', '" + std::to_string(in_year) + "', '" + std::to_string(in_credits) + "');";
}
string Admin::remove_course(string in_course_name, int in_CRN, string in_Department, string in_Instructor, string in_time, string in_Doftw, string in_Semester, int in_year, int in_credits) {
	//cout << "Course Removed!";
	return "DELETE FROM COURSE WHERE CRN = " + std::to_string(in_CRN) + " AND TITLE = '" + in_course_name + "' AND DEPARTMENT = '" + in_Department + "' AND INSTRUCTOR = '" + in_Instructor + "' AND TIME = '" + in_time + "' AND Dofw = '" + in_Doftw + "' AND SEMESTER = '" + in_Semester + "' AND YEAR = " + std::to_string(in_year) + " AND CREDITS = " + std::to_string(in_credits) + ";";
}
string Admin::add_user(string in_user_add_f, string in_user_add_l, string in_user_add_ID, string in_user_add_Grad_year, string in_user_add_Major, string in_user_add_Email, int add_user_type, string user_add_Title, string user_add_YOH, string user_add_Department, string user_add_Office) {
	string user_type_str;
	switch (add_user_type){
		case 3:
			if (add_user_type == 3) { user_type_str = "admin"; }
			return "INSERT INTO ADMIN VALUES(" + in_user_add_ID + ", '" + in_user_add_f + "', '" + in_user_add_l + "', '" + user_type_str + "', '" + user_add_Office + "', '" + in_user_add_Email + "');";
		break;

		case 2:
			if (add_user_type == 2) { user_type_str = "instructor"; }
			return "INSERT INTO INSTRUCTOR VALUES(" + in_user_add_ID + ", '" + in_user_add_f + "', '" + in_user_add_l + "', '" + user_add_Title + "', " + user_add_YOH + ", '" + user_add_Department + "', '" + in_user_add_Email + "');";
		break;

		case 1:
			if (add_user_type == 1) { user_type_str = "student"; }
			return "INSERT INTO STUDENT VALUES(" + in_user_add_ID + ", '" + in_user_add_f + "', '" + in_user_add_l + "', " + in_user_add_Grad_year + ", '" + in_user_add_Major + "', '" + in_user_add_Email + "');";
		break;
	}
}
string Admin::remove_user(string in_user_removef, string in_user_removel, string in_user_remove_ID, string in_user_remove_Grad_year, string in_user_remove_Major, string in_user_remove_Email, int remove_user_type, string user_remove_Title, string user_remove_YOH, string user_remove_Department, string user_remove_Office) {
	string user_type_str;
	switch (remove_user_type) {
	case 3:
		if (remove_user_type == 3) { user_type_str = "admin"; }
			return "DELETE FROM ADMIN WHERE ID = " + in_user_remove_ID + " AND NAME = '" + in_user_removef + "' AND SURNAME = '" + in_user_removel + "' AND OFFICE = '" + user_remove_Office + "' AND EMAIL = '" + in_user_remove_Email + "';";
		break;

		case 2:
			if (remove_user_type == 2) { user_type_str = "instructor"; }
			return "DELETE FROM INSTRUCTOR WHERE ID = " + in_user_remove_ID + " AND NAME = '" + in_user_removef + "' AND SURNAME = '" + in_user_removel + "' AND TITLE = '" + user_remove_Title + "' AND HIREYEAR = " + user_remove_YOH + " AND DEPT = '" + user_remove_Department + "' AND EMAIL = '" + in_user_remove_Email + "';";
		break;

		case 1:
			if (remove_user_type == 1) { user_type_str = "student"; }
			return "DELETE FROM STUDENT WHERE ID = " + in_user_remove_ID + " AND NAME = '" + in_user_removef + "' AND SURNAME = '" + in_user_removel + "' AND GRADYEAR = " + in_user_remove_Grad_year + " AND MAJOR = '" + in_user_remove_Major + "' AND EMAIL = '" + in_user_remove_Email + "';";
		break;
	}
}
void Admin::add_student_course(string in_student, string in_course) {
	//cout << "Student Added to Course!";
	cout << in_student << " Added to " << in_course << "!" << endl;
}
void Admin::remove_student_course(string in_student, string in_course) {
	//cout << "Student Removed from Course!";
	cout << in_student << " Removed from " << in_course << "!" << endl;
}
void Admin::search_roster(string in_course_search_roster) {
	cout << "Roster Searched!" << endl;
}
void Admin::print_roster(string in_course_print_roster) {
	cout << "Roster Printed!" << endl;
}
void Admin::search_courses(string in_course) {
	cout << "Course Searched!" << endl;
}
void Admin::print_courses(string in_course) {
	cout << "Course Printed!" << endl;
}
//destructor
Admin::~Admin() {

}
