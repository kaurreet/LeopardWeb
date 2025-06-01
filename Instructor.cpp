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
    sqlite3* db;
    sqlite3_stmt* stmt;
    int exit = sqlite3_open("assignment3.db", &db);

    if (exit) {
        cout << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    string sql = "SELECT * FROM COURSE WHERE INSTRUCTOR = ?;";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    string full_name = first_name + " " + last_name;  // or use ID
    sqlite3_bind_text(stmt, 1, full_name.c_str(), -1, SQLITE_STATIC);

    cout << "Instructor Schedule\n";
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
            << "Time: " << time << " | " << days << "\n"
            << "Semester: " << semester << " " << year << "\n"
            << "Credits: " << credits << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
	cout << "Schedule Printed!" << endl;

}
//destructor
Instructor::~Instructor() {

}