#include "Instructor.h"
#include <iostream>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::string;
extern "C" {
#include "sqlite3.h"
}
//constructor
Instructor::Instructor(string in_fname, string in_lname, int in_ID) {
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
//void Instructor::search_course(sqlite3* db, string course_add_drop, int Course_CRN, string department_course, string course_instructor, string course_start_time, string Meeting_times, string course_semester, int course_year, int course_credits) {
//	sqlite3_stmt* stmt;
//	//int rc = sqlite3_open("assignment3.db", &db);
//	const char* sql = R"(
//        SELECT * FROM COURSE
//        WHERE CRN = ? AND TITLE = ? AND DEPARTMENT = ? AND INSTRUCTOR = ? AND TIME = ? AND
//              DoftW = ? AND SEMESTER = ? AND YEAR = ? AND CREDITS = ?)";
//
//	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
//	if (rc != SQLITE_OK) {
//		std::cerr << "Failed to prepare statement. Error: " << sqlite3_errmsg(db) << std::endl;
//		return;
//	}
//
//	sqlite3_bind_int(stmt, 1, Course_CRN);
//	sqlite3_bind_text(stmt, 2, course_add_drop.c_str(), -1, SQLITE_TRANSIENT);
//	sqlite3_bind_text(stmt, 3, department_course.c_str(), -1, SQLITE_TRANSIENT);
//	sqlite3_bind_text(stmt, 4, course_instructor.c_str(), -1, SQLITE_TRANSIENT);
//	sqlite3_bind_text(stmt, 5, course_start_time.c_str(), -1, SQLITE_TRANSIENT);
//	sqlite3_bind_text(stmt, 6, Meeting_times.c_str(), -1, SQLITE_TRANSIENT);
//	sqlite3_bind_text(stmt, 7, course_semester.c_str(), -1, SQLITE_TRANSIENT);
//	sqlite3_bind_int(stmt, 8, course_year);
//	sqlite3_bind_int(stmt, 9, course_credits);
//
//	rc = sqlite3_step(stmt);
//	if (rc == SQLITE_ROW) {
//		cout << "Course found in the database!" << endl;
//	}
//	else {
//		cout << "Course NOT found in the database!" << endl;
//	}
//	sqlite3_finalize(stmt);
//}
string Instructor::search_course(sqlite3* db, string course_add_drop, string in_fname, string in_lname) {
	//string search_print_roster;
	//search_print_roster = "SELECT * FROM ";
	string sql = "SELECT STUDENT.NAME, STUDENT.SURNAME, STUDENT.ID "
				 "FROM STUDENT "
				 "JOIN REGISTERED ON STUDENT.ID = REGISTERED.StudentID "
				 "JOIN COURSE ON REGISTERED.CRN = COURSE.CRN "
				 "WHERE COURSE.TITLE = '" + course_add_drop + "' "
				 "AND COURSE.INSTRUCTOR = '" + in_fname + " " + in_lname + "';";
	return sql;
}
void Instructor::print_class_list(string &student_query) {
	student_query = "SELECT * FROM STUDENT;";
}
string Instructor::print_schedule(string in_fname, string in_lname) {
	return "SELECT * FROM COURSE WHERE INSTRUCTOR = '" + in_fname + " " + in_lname + "';";
}
//destructor
Instructor::~Instructor() {

}
