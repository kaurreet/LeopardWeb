#include "Admin.h"
#include <iostream>
#include <algorithm>
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
void Admin::add_course(string in_course) {
	//cout << "Course Added!";
	cout << in_course << " Course Added!" << endl;
}
void Admin::remove_course(string in_course) {
	//cout << "Course Removed!";
	cout << in_course << " Course Removed!" << endl;
}
void Admin::add_user(string in_user) {
	cout << "User Added!" << endl;
}
void Admin::remove_user(string in_user) {
	cout << "User Removed!" << endl;
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
