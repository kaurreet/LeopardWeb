#include <iostream>
#include <algorithm>
#include "Student.h"
extern "C" {
#include "sqlite3.h"
}
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
void Student::search_course(sqlite3* db, string course_add_drop, int Course_CRN, string department_course, string course_instructor, string course_start_time, string Meeting_times, string course_semester, int course_year, int course_credits) {
	sqlite3_stmt* stmt;
	//int rc = sqlite3_open("assignment3.db", &db);
	const char* sql = R"(
        SELECT * FROM COURSE
        WHERE CRN = ? AND TITLE = ? AND DEPARTMENT = ? AND INSTRUCTOR = ? AND TIME = ? AND
              DofW = ? AND SEMESTER = ? AND YEAR = ? AND CREDITS = ?)";

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
string Student::add_course(string in_course_name, int in_CRN, string in_Department, string in_Instructor, string in_time, string in_Doftw, string in_Semester, int in_year, int in_credits){
	//cout << "Course Added!";
	return "INSERT INTO COURSE VALUES(" + std::to_string(in_CRN) + ", '" + in_course_name + "', '" + in_Department + "', '" + in_Instructor + "', '" + in_time + "', '" + in_Doftw + "', '" + in_Semester + "', '" + std::to_string(in_year) + "', '" + std::to_string(in_credits) + "');";
}
string Student::remove_course(string course_remove, int Course_CRN, string department_course, string course_instructor, string course_start_time, string Meeting_times, string course_semester, int course_year, int course_credits) {
	//cout << "Course Added!";
	return "DELETE FROM COURSE WHERE CRN = " + std::to_string(Course_CRN) + " AND TITLE = '" + course_remove + "' AND DEPARTMENT = '" + department_course + "' AND INSTRUCTOR = '" + course_instructor + "' AND TIME = '" + course_start_time + "' AND Dofw = '" + Meeting_times + "' AND SEMESTER = '" + course_semester + "' AND YEAR = " + std::to_string(course_year) + " AND CREDITS = " + std::to_string(course_credits) + ";";
}
string Student::print_schedule() {
	return "SELECT * FROM COURSE;";
}
//destructor
Student::~Student() {

}
