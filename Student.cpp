#include <iostream>
#include <algorithm>
#include "Student.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
//constructor
Student::Student() {
	first_name = "Andy";
	last_name = "Le";
}
Student::Student(string in_fname, string in_lname, string in_ID) {
	first_name = in_fname;
	last_name = in_lname;
	ID = in_ID;
}
//methods
void Student::show_first_name() {
	cout << first_name << endl;
	//return first_name;
	
}
void Student::show_last_name() {
	cout << last_name << endl;
	//return last_name;
	
}
void Student::show_ID() {
	cout << ID << endl;
	//return ID;
	
}
void Student::show_all() {
	cout << first_name << endl;
	cout << last_name << endl;
	cout << ID << endl;
	//return first_name, last_name, ID;
	
}
void Student::search_course(string in_course) {
	cout << in_course << " Course Searched!" << endl;
	
}
void Student::add_drop_course(string in_course, string in_add_drop){
	std::transform(in_add_drop.begin(), in_add_drop.end(), in_add_drop.begin(), ::tolower);
	std::transform(in_course.begin(), in_course.end(), in_course.begin(), ::toupper);

	if (in_add_drop == "add")
	{
		cout << in_course << " Course Added!" << endl;
	}
	else if (in_add_drop == "drop")
	{
		cout << in_course << " Course Dropped!" << endl;
	}
	else {
		cout << "Neither add or drop was chosen." << endl;
	}
	
}
void Student::print_schedule() {
	cout << "Schedule Printed!" << endl;
	
}
//destructor
Student::~Student() {

}