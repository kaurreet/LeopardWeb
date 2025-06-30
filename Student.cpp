#include <iostream>
#include <algorithm>
#include "Student.h"
#include <string>
#include "Course.h"
//#include "assignment_1.cpp"
extern "C" {
#include "sqlite3.h"
}
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
//constructor
Student::Student() {}

Student::Student(string in_fname, string in_lname, int in_ID) : User(in_fname, in_lname, in_ID){
	first_name = in_fname;
	last_name = in_lname;
	ID = in_ID;
}

void Student::set_firstname(string in_fname) {
	first_name = in_fname;
}
void Student::set_lastname(string in_lname) {
	last_name = in_lname;
}
void Student::set_ID(int in_ID) {
	ID = in_ID;
}

void Student::set_email(string in_email) {
	email = in_email;
}

void Student::set_gradYear(int in_gradyear) {
	gradYear = in_gradyear;
}

void Student::set_major(string in_major) {
	major = in_major;
}

string Student::get_firstname() {
	return first_name;
}
string Student::get_lastname() {
	return last_name;
}
int Student::get_ID() {
	return ID;
}

string Student::get_email() {
	return email;
}

int Student::get_gradYear() {
	return gradYear;
}

string Student::get_major() {
	return major;
}

//methods
//void Student::search_course(sqlite3* db, string course_add_drop, int in_ID, int (*callback)(void*, int, char**, char**)) {
//	sqlite3_stmt* stmt;
//	Course temp_c1;
//	string sql;
//	//int rc = sqlite3_open("assignment3.db", &db);
//	if (course_add_drop == "all")
//	{
//		sql = "SELECT * FROM COURSE;";
//	}
//	//else
//		//sql = "SELECT * FROM REGISTERED WHERE TITLE = ? AND StudentID = ?;";
//
//	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
//	if (rc != SQLITE_OK) {
//		std::cerr << "Failed to prepare statement. Error: " << sqlite3_errmsg(db) << std::endl;
//		return;
//	}
//
//	// Bind course title and student ID
//	//sqlite3_bind_text(stmt, 1, course_add_drop.c_str(), -1, SQLITE_TRANSIENT);
//	//sqlite3_bind_int(stmt, 2, in_ID);
//
//	rc = sqlite3_step(stmt);
//	if (rc == SQLITE_ROW && course_add_drop != "all") {
//		// Extract and print course attributes
//		temp_c1.set_CRN(sqlite3_column_int(stmt, 0));
//		temp_c1.set_title(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
//		temp_c1.set_department(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
//		temp_c1.set_instructor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
//		temp_c1.set_starttime(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
//		temp_c1.set_meetingtime(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
//		temp_c1.set_semester(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
//		temp_c1.set_year(sqlite3_column_int(stmt, 7));
//		temp_c1.set_credits(sqlite3_column_int(stmt, 8));
//		//temp_c1.set_studentID(sqlite3_column_int(stmt, 8)); // last column
//		cout << "Course found:\n";
//		cout << "CRN: " << temp_c1.get_CRN() << endl;
//		cout << "Title: " << temp_c1.get_title() << endl;
//		cout << "Department: " << temp_c1.get_department() << endl;
//		cout << "Instructor: " << temp_c1.get_instructor() << endl;
//		cout << "Start Time: " << temp_c1.get_time() << endl;
//		cout << "Meeting Times: " << temp_c1.get_days() << endl;
//		cout << "Semester: " << temp_c1.get_semester() << endl;
//		cout << "Year: " << temp_c1.get_year() << endl;
//		cout << "Credits: " << temp_c1.get_credits() << endl;
//
//	}
//	else if (rc == SQLITE_ROW && course_add_drop == "all") {
//		string query = "SELECT * FROM COURSE;";
//
//		cout << endl << query << endl;		//print the string to screen
//
//		// you need the callback function this time since there could be multiple rows in the table
//		sqlite3_exec(db, query.c_str(), callback, NULL, NULL);
//	}
//	else {
//		cout << "Course NOT found in the database!" << endl;
//	}
//
//	sqlite3_finalize(stmt);
//}

string Student::search_course(sqlite3* db, string course_add_drop, int in_CRN, string in_dep, string in_instruct, string in_parameter) {
	string sql;

	if (in_parameter == "no") {
		sql = "SELECT * FROM COURSE;";
	}
	else if (in_parameter == "name") {
		sql = "SELECT * FROM COURSE WHERE TITLE = '" + course_add_drop + "';";
	}
	else if (in_parameter == "crn") {
		sql = "SELECT * FROM COURSE WHERE CRN = " + to_string(in_CRN) + ";";
	}
	else if (in_parameter == "dep") {
		sql = "SELECT * FROM COURSE WHERE DEPARTMENT = '" + course_add_drop + "';";
	}
	else if (in_parameter == "instructor") {
		sql = "SELECT * FROM COURSE WHERE INSTRUCTOR = '" + in_instruct + "';";
	}

	return sql;
}

string Student::add_course(sqlite3* DB, string in_course_name, int ID){
	string sql = "INSERT INTO REGISTERED (CRN, TITLE, DEPARTMENT, TIME, doftw, SEMESTER, YEAR, CREDITS, StudentID)"
		"SELECT CRN, TITLE, DEPARTMENT, TIME, DoftW, SEMESTER, YEAR, CREDITS, " + to_string(ID) + " " + "FROM COURSE WHERE TITLE = '" + in_course_name + "';";
	return sql;
}
string Student::remove_course(sqlite3* DB, string in_course_name, int ID) {
	//cout << "Course Added!";
	return "DELETE FROM REGISTERED WHERE TITLE = '" + in_course_name + "' AND studentID = '" + to_string(ID) + "';";
}
string Student::print_schedule() {
	return "SELECT * FROM REGISTERED WHERE StudentID = " + to_string(ID) + ";";
}
//destructor
Student::~Student() {

}
