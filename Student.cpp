#include <iostream>
#include <algorithm>
#include "Student.h"
#include <string>
extern "C" {
#include "sqlite3.h"
}
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
//constructor
Student::Student(string in_fname, string in_lname, int in_ID) : User(in_fname, in_lname, in_ID){
	first_name = in_fname;
	last_name = in_lname;
	ID = in_ID;
}
//methods
void Student::search_course(sqlite3* db, string course_add_drop, int Course_CRN, string department_course, string course_instructor, string course_start_time, string Meeting_times, string course_semester, int course_year, int course_credits) {
	sqlite3_stmt* stmt;
	//int rc = sqlite3_open("assignment3.db", &db);
	const char* sql = R"(
        SELECT * FROM COURSE
        WHERE CRN = ? AND TITLE = ? AND DEPARTMENT = ? AND INSTRUCTOR = ? AND TIME = ? AND
              DoftW = ? AND SEMESTER = ? AND YEAR = ? AND CREDITS = ?)";

	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement. Error: " << sqlite3_errmsg(db) << std::endl;
		return;
	}

	sqlite3_bind_int(stmt, 1, Course_CRN);
	sqlite3_bind_text(stmt, 2, course_add_drop.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, department_course.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 4, course_instructor.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 5, course_start_time.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 6, Meeting_times.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 7, course_semester.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 8, course_year);
	sqlite3_bind_int(stmt, 9, course_credits);

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		cout << "Course found in the database!" << endl;
	}
	else {
		cout << "Course NOT found in the database!" << endl;
	}
	sqlite3_finalize(stmt);	
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
