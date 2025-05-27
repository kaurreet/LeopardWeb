#include "Instructor.h"
#include <iostream>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::string;
//constructor
Instructor::Instructor() {
	first_name = "Andy";
	last_name = "Le";
}
Instructor::Instructor(string in_fname, string in_lname, string in_ID) {
	first_name = in_fname;
	last_name = in_lname;
	ID = in_ID;
}
//methods
void Instructor::show_first_name() {
	cout << first_name << endl;
	//return first_name;

}
void Instructor::show_last_name() {
	cout << last_name << endl;
	//return last_name;

}
void Instructor::show_ID() {
	cout << ID << endl;
	//return ID;

}
void Instructor::show_all() {
	cout << first_name << endl;
	cout << last_name << endl;
	cout << ID << endl;
	//return first_name, last_name, ID;

}
void Instructor::search_course(string in_course) {
	cout << "Course Searched!" << endl;

}
void Instructor::print_class_list(string in_course) {
	cout << "Class List Printed!" << endl;

}
void Instructor::print_schedule() {
	cout << "Schedule Printed!" << endl;

}
//destructor
Instructor::~Instructor() {

}