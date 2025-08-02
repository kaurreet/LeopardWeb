#include "Instructor.h"
#include <iostream>
#include <algorithm>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
extern "C" {
#include "sqlite3.h"
}
//constructor

Instructor::Instructor(string in_fname, string in_lname, int in_ID) {
	first_name = in_fname;
	last_name = in_lname;
	ID = in_ID;
}

Instructor::Instructor(string in_fname, string in_lname, int in_ID, string in_email, string in_title, int in_YOH, string in_department){
	first_name = in_fname;
	last_name = in_lname;
	ID = in_ID;
	email = in_email;
	title = in_title;
	YOH = in_YOH;
	department = in_department;
}
//methods
string Instructor::get_first_name() {
	//cout << first_name << endl;
	return first_name;

}
string Instructor::get_last_name() {
	//cout << last_name << endl;
	return last_name;

}
int Instructor::get_ID() {
	cout << ID << endl;
	return ID;

}

string Instructor::get_title() {
	return title;
}

int Instructor::get_YOH() {
	return YOH;
}

string Instructor::get_Department() {
	return department;
}

//string Instructor::get_all() {
//	cout << first_name << endl;
//	cout << last_name << endl;
//	cout << ID << endl;
//	return first_name, last_name, ID;
//
//}
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
//string Instructor::search_course(sqlite3* db, string course_add_drop, string in_fname, string in_lname) {
//	//string search_print_roster;
//	//search_print_roster = "SELECT * FROM ";
//	string sql = "SELECT STUDENT.NAME, STUDENT.SURNAME, STUDENT.ID "
//				 "FROM STUDENT "
//				 "JOIN REGISTERED ON STUDENT.ID = REGISTERED.StudentID "
//				 "JOIN COURSE ON REGISTERED.CRN = COURSE.CRN "
//				 "WHERE COURSE.TITLE = '" + course_add_drop + "' "
//				 "AND COURSE.INSTRUCTOR = '" + in_fname + " " + in_lname + "';";
//	return sql;
//}
string Instructor::search_course(sqlite3* db, string course_add_drop, int in_CRN, string in_dep, string in_instruct, string in_parameter) {
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

void Instructor::print_class_list(string &student_query) {
	student_query = "SELECT * FROM STUDENT;";
}
string Instructor::print_schedule(string in_fname, string in_lname) {
	return "SELECT * FROM COURSE WHERE INSTRUCTOR = '" + in_fname + " " + in_lname + "';";
}

void Instructor::set_title(string in_title) {
	title = in_title;
}
void Instructor::set_YOH(int in_YOH) {
	YOH = in_YOH;
}
void Instructor::set_Department(string in_department) {
	department = in_department;
}


string Instructor::get_studentname(int student_id) {
	return "SELECT NAME, SURNAME FROM STUDENT WHERE ID = " + std::to_string(student_id) + ";";
}

string Instructor::getstudent_classlist(int in_student_id) {
	return "SELECT COURSE.CRN, COURSE.TITLE, COURSE.DEPARTMENT, COURSE.INSTRUCTOR "
	       "FROM COURSE "
	       "JOIN REGISTERED ON COURSE.CRN = REGISTERED.CRN "
		   "WHERE REGISTERED.StudentID = '" + to_string(in_student_id) + "';";
}

string Instructor::getcourse_roster(string title) {
	return "SELECT STUDENT.ID, STUDENT.NAME, STUDENT.SURNAME "
		"FROM STUDENT "
		"JOIN REGISTERED ON STUDENT.ID = REGISTERED.StudentID "
		"WHERE REGISTERED.TITLE = '" + title +"';";
}

string Instructor::get_courseinfo(string title) {
	return "SELECT TITLE, INSTRUCTOR, CRN FROM COURSE WHERE TITLE = '" + title + "';";
}


void Instructor::set_email(string in_email) {
	email = in_email;
}

//destructor
Instructor::~Instructor() {

}
