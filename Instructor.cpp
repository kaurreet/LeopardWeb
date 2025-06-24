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
	if (courses_taught.find(in_course) != courses_taught.end())
		cout << in_course << " is on this instructor's schedule." << endl;
	else
		cout << in_course << " is not in the instructor's course list." << endl;
}
void Instructor::print_class_list(string in_course) {
	cout << "Class List for " << in_course << "has been Printed!" << endl;

}
void Instructor::print_schedule() {
	if (courses_taught.empty())
		cout << "Schedule Printed!" << endl;
	else
		cout << "Instructor's Schedule:" << endl;
		

}
//destructor
Instructor::~Instructor() {

}
