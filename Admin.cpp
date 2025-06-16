#include "Admin.h"
#include <iostream>
#include <algorithm>
#include "sqlite3.h"
extern "C" {
#include "sqlite3.h"
}
using std::cin;
using std::cout;
using std::endl;
using std::string;

Admin::Admin(string in_fname, string in_lname, int in_ID) {
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
string Admin::add_course(string in_course_name, int in_CRN, string in_Department, string in_Instructor, string in_time, string in_Doftw, string in_Semester, int in_year, int in_credits) {
	//cout << "Course Added!";
	return "INSERT INTO COURSE VALUES(" + std::to_string(in_CRN) + ", '" + in_course_name + "', '" + in_Department + "', '" + in_Instructor + "', '" + in_time + "', '" + in_Doftw + "', '" + in_Semester + "', '" + std::to_string(in_year) + "', '" + std::to_string(in_credits) + "');";
}
string Admin::remove_course(string in_course_name, int in_CRN, string in_Department, string in_Instructor, string in_time, string in_Doftw, string in_Semester, int in_year, int in_credits) {
	//cout << "Course Removed!";
	return "DELETE FROM COURSE WHERE CRN = " + std::to_string(in_CRN) + " AND TITLE = '" + in_course_name + "' AND DEPARTMENT = '" + in_Department + "' AND INSTRUCTOR = '" + in_Instructor + "' AND TIME = '" + in_time + "' AND Doftw = '" + in_Doftw + "' AND SEMESTER = '" + in_Semester + "' AND YEAR = " + std::to_string(in_year) + " AND CREDITS = " + std::to_string(in_credits) + ";";
}
string Admin::add_user(string in_user_add_f, string in_user_add_l, string in_user_add_ID, string in_user_add_Grad_year, string in_user_add_Major, string in_user_add_Email, int add_user_type, string user_add_Title, string user_add_YOH, string user_add_Department, string user_add_Office) {
	string user_type_str;
	switch (add_user_type){
		case 3:
			if (add_user_type == 3) { user_type_str = "admin"; }
			return "INSERT INTO ADMIN VALUES(" + in_user_add_ID + ", '" + in_user_add_f + "', '" + in_user_add_l + "', '" + user_type_str + "', '" + user_add_Office + "', '" + in_user_add_Email + "');";
		break;

		case 2:
			if (add_user_type == 2) { user_type_str = "instructor"; }
			return "INSERT INTO INSTRUCTOR VALUES(" + in_user_add_ID + ", '" + in_user_add_f + "', '" + in_user_add_l + "', '" + user_add_Title + "', " + user_add_YOH + ", '" + user_add_Department + "', '" + in_user_add_Email + "');";
		break;

		case 1:
			if (add_user_type == 1) { user_type_str = "student"; }
			return "INSERT INTO STUDENT VALUES(" + in_user_add_ID + ", '" + in_user_add_f + "', '" + in_user_add_l + "', " + in_user_add_Grad_year + ", '" + in_user_add_Major + "', '" + in_user_add_Email + "');";
		break;
	}
}
string Admin::remove_user(string in_user_removef, string in_user_removel, string in_user_remove_ID, string in_user_remove_Grad_year, string in_user_remove_Major, string in_user_remove_Email, int remove_user_type, string user_remove_Title, string user_remove_YOH, string user_remove_Department, string user_remove_Office) {
	string user_type_str;
	switch (remove_user_type) {
	case 3:
		if (remove_user_type == 3) { user_type_str = "admin"; }
			return "DELETE FROM ADMIN WHERE ID = " + in_user_remove_ID + " AND NAME = '" + in_user_removef + "' AND SURNAME = '" + in_user_removel + "' AND OFFICE = '" + user_remove_Office + "' AND EMAIL = '" + in_user_remove_Email + "';";
		break;

		case 2:
			if (remove_user_type == 2) { user_type_str = "instructor"; }
			return "DELETE FROM INSTRUCTOR WHERE ID = " + in_user_remove_ID + " AND NAME = '" + in_user_removef + "' AND SURNAME = '" + in_user_removel + "' AND TITLE = '" + user_remove_Title + "' AND HIREYEAR = " + user_remove_YOH + " AND DEPT = '" + user_remove_Department + "' AND EMAIL = '" + in_user_remove_Email + "';";
		break;

		case 1:
			if (remove_user_type == 1) { user_type_str = "student"; }
			return "DELETE FROM STUDENT WHERE ID = " + in_user_remove_ID + " AND NAME = '" + in_user_removef + "' AND SURNAME = '" + in_user_removel + "' AND GRADYEAR = " + in_user_remove_Grad_year + " AND MAJOR = '" + in_user_remove_Major + "' AND EMAIL = '" + in_user_remove_Email + "';";
		break;
	}
}
string Admin::update_user(sqlite3* db, string user_searchf, string user_searchl, string user_search_ID, string user_search_Grad_year, string user_update_Grad_year, string user_search_Major, string user_update_major, string user_search_Email, int search_user_type, string user_search_Title, string user_update_Title, string user_search_YOH, string user_search_Department, string user_add_Office) {
	//sqlite3* db;
	char* errMsg = nullptr;

	// Open the SQLite database
	//int rc = sqlite3_open("course_management.db", &db);
	//if (rc) {
	//	return "Can't open database: " + string(sqlite3_errmsg(db));
	//}

	string sql;
	string user_type_str;

	switch (search_user_type) {
		case 3:  // Admin
			sql = "UPDATE ADMIN SET "
				"NAME = '" + user_searchf + "', "
				"SURNAME = '" + user_searchl + "', "
				"TITLE = '" + user_update_Title + "', "
				"OFFICE = '" + user_add_Office + "', "
				"EMAIL = '" + user_search_Email + "' "
				"WHERE ID = '" + user_search_ID + "';";
		break;

		case 2:  // Instructor
			sql = "UPDATE INSTRUCTOR SET "
				"NAME = '" + user_searchf + "', "
				"SURNAME = '" + user_searchl + "', "
				"TITLE = '" + user_update_Title + "', "
				"HIREYEAR = '" + user_search_YOH + "', "
				"DEPT = '" + user_search_Department + "', "
				"EMAIL = '" + user_search_Email + "' "
				"WHERE ID = '" + user_search_ID + "';";
		break;

		case 1:  // Student
			sql = "UPDATE STUDENT SET "
				"NAME = '" + user_searchf + "', "
				"SURNAME = '" + user_searchl + "', "
				"GRADYEAR = '" + user_update_Grad_year + "', "
				"MAJOR = '" + user_update_major + "', "
				"EMAIL = '" + user_search_Email + "' "
				"WHERE ID = '" + user_search_ID + "';";
		break;
	}

	std::cout << "Exeuting SQL: " << sql << std::endl;  // Debug output

	int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
	string result;

	if (rc != SQLITE_OK) {
		result = "SQL error: " + string(errMsg);
		sqlite3_free(errMsg);
	}
	else {
		result = "User updated successfully.";
	}

	return result;
}
void Admin::add_student_course(string in_student, string in_course) {
	//cout << "Student Added to Course!";
	cout << in_student << " Added to " << in_course << "!" << endl;
}
void Admin::remove_student_course(string in_student, string in_course) {
	//cout << "Student Removed from Course!";
	cout << in_student << " Removed from " << in_course << "!" << endl;
}
void Admin::search_roster(sqlite3* db, string user_searchf, string user_searchl, string user_search_ID, string user_search_Grad_year, string user_search_Major, string user_search_Email, string search_user_type, string user_search_Title, string user_search_YOH, string user_search_Department, string user_search_Office) {
	sqlite3_stmt* stmt;
	const char* sql ="";
	//int rc = sqlite3_open("assignment3.db", &db);
	if (search_user_type == "STUDENT") {
		sql = R"(
        SELECT * FROM STUDENT
        WHERE ID = ? AND NAME = ? AND SURNAME = ? AND GRADYEAR = ? AND MAJOR = ? AND
              EMAIL = ?)";
	} else if (search_user_type == "INSTRUCTOR") {
		sql = R"(
        SELECT * FROM INSTRUCTOR
        WHERE ID = ? AND NAME = ? AND SURNAME = ? AND TITLE = ? AND HIREYEAR = ? AND DEPT = ? AND
              EMAIL = ?)";
	} else if (search_user_type == "ADMIN") {
		sql = R"(
        SELECT * FROM ADMIN
        WHERE ID = ? AND NAME = ? AND SURNAME = ? AND TITLE = ? AND OFFICE = ? AND
              EMAIL = ?)";
	}


	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Failed to prepare statement. Error: " << sqlite3_errmsg(db) << std::endl;
		return;
	}

	if (search_user_type == "STUDENT") {
		sqlite3_bind_int(stmt, 1, std::stoi(user_search_ID));
		sqlite3_bind_text(stmt, 2, user_searchf.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 3, user_searchl.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 4, user_search_Grad_year.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 5, user_search_Major.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 6, user_search_Email.c_str(), -1, SQLITE_TRANSIENT);
	}
	else if (search_user_type == "INSTRUCTOR") {
		sqlite3_bind_int(stmt, 1, std::stoi(user_search_ID));
		sqlite3_bind_text(stmt, 2, user_searchf.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 3, user_searchl.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 4, user_search_Title.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 5, user_search_YOH.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 6, user_search_Department.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 7, user_search_Email.c_str(), -1, SQLITE_TRANSIENT);
	}
	else if (search_user_type == "ADMIN") {
		sqlite3_bind_int(stmt, 1, std::stoi(user_search_ID));
		sqlite3_bind_text(stmt, 2, user_searchf.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 3, user_searchl.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 4, user_search_Title.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 5, user_search_Office.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 6, user_search_Email.c_str(), -1, SQLITE_TRANSIENT);
	}
	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		cout << "User found in the database!" << endl;
	}
	else {
		cout << "User NOT found in the database!" << endl;
	}
	sqlite3_finalize(stmt);
}
void Admin::print_roster(string &student_query, string &instructor_query, string &admin_query) {
	student_query = "SELECT * FROM STUDENT;"; instructor_query = "SELECT * FROM INSTRUCTOR;"; admin_query = "SELECT * FROM ADMIN;";
}
void Admin::search_courses(sqlite3* db, string course_add_drop, int Course_CRN, string department_course, string course_instructor, string course_start_time, string Meeting_times, string course_semester, int course_year, int course_credits) {
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
string Admin::print_courses(string in_course) {
	string query;
	if (in_course == "all") {
		query = "SELECT * FROM COURSE";
	}
	else
		query = "SELECT * FROM COURSE WHERE TITLE LIKE '%" + in_course + "%';";
	return query;
}
//destructor
Admin::~Admin() {

}
