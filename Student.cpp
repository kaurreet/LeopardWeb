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
void Student::print_schedule() 
{
	sqlite3* db;
	sqlite3_stmt* stmt;
	int exit = sqlite3_open("assignment3.db", &db); // Replace with your actual DB

	if (exit) {
		cout << "Error opening database: " << sqlite3_errmsg(db) << endl;
		return;
	}

	string sql = "SELECT C.* FROM COURSE C "
		"JOIN STUDENT_COURSE SC ON C.CRN = SC.CRN "
		"WHERE SC.STUDENT_ID = ?;";

	if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return;
	}

	sqlite3_bind_text(stmt, 1, ID.c_str(), -1, SQLITE_STATIC);

	cout << "Student Course Schedule \n";
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int crn = sqlite3_column_int(stmt, 0);
		string title = (const char*)sqlite3_column_text(stmt, 1);
		string dept = (const char*)sqlite3_column_text(stmt, 2);
		string instructor = (const char*)sqlite3_column_text(stmt, 3);
		string time = (const char*)sqlite3_column_text(stmt, 4);
		string days = (const char*)sqlite3_column_text(stmt, 5);
		string semester = (const char*)sqlite3_column_text(stmt, 6);
		int year = sqlite3_column_int(stmt, 7);
		int credits = sqlite3_column_int(stmt, 8);

		cout << "CRN: " << crn << "\n"
			<< "Title: " << title << "\n"
			<< "Instructor: " << instructor << "\n"
			<< "Time: " << time << " | " << days << "\n"
			<< "Semester: " << semester << " " << year << "\n"
			<< "Credits: " << credits << "\n";
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	cout << "Schedule Printed!" << endl;
	
}
//destructor
Student::~Student() {

}