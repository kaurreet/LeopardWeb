
#include <iostream>
#include <algorithm>
#include <set>
#include "User.h"
#include "Student.h"
#include "Instructor.h"
#include "Admin.h"
#include "Course.h"
#include "Login.h"
extern "C" {
	#include "sqlite3.h"
}
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::set;
using std::to_string;

static int callback(void* data, int argc, char** argv, char** azColName)
{
	int i;
	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void create_table(sqlite3* db, const string& sql) {
	char* messageError;
	int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK)
	{
		//std::cerr << "Error Create Table: " << messageError << endl;
		sqlite3_free(messageError);
	}
	else {
		//cout << "Table created Successfully" << endl;
	}
}

void create_tables(sqlite3* db) {
	// Create Course Table
	string tableCourse = "CREATE TABLE IF NOT EXISTS COURSE(" //database Course table
		"CRN INTEGER PRIMARY KEY NOT NULL, "
		"TITLE TEXT NOT NULL, "
		"DEPARTMENT TEXT NOT NULL, "
		"INSTRUCTOR TEXT NOT NULL, "
		"TIME TEXT NOT NULL,"
		"DoftW TEXT NOT NULL,"
		"SEMESTER TEXT NOT NULL,"
		"YEAR INTEGER NOT NULL,"
		"CREDITS INTEGER NOT NULL); ";

	// Create Enrollment Table
	string studentEnrolledTable = "CREATE TABLE IF NOT EXISTS REGISTERED("
		"CRN INT NOT NULL, "
		"TITLE TEXT NOT NULL, "
		"DEPARTMENT TEXT NOT NULL, "
		"TIME TEXT NOT NULL, "
		"DoftW TEXT NOT NULL, "
		"SEMESTER TEXT NOT NULL, "
		"YEAR INT NOT NULL, "
		"CREDITS INT NOT NULL, "
		"StudentID TEXT NOT NULL, "
		"PRIMARY KEY (CRN, StudentID));";

	// Create Student Table
	string tableStudent = "CREATE TABLE IF NOT EXISTS STUDENT("  //database Student table
		"ID INTEGER PRIMARY KEY, "
		"NAME TEXT NOT NULL, "
		"SURNAME TEXT NOT NULL, "
		"GRADYEAR INTEGER NOT NULL,"
		"MAJOR TEXT NOT NULL,"
		"EMAIL TEXT NOT NULL); ";

	string RosterTable = "CREATE TABLE IF NOT EXISTS ROSTER("
		"STUDENT_CRN TEXT NOT NULL, "
		"STUDENT_SECTION TEXT NOT NULL, "
		"STUDENT_FIRSTNAME TEXT, "
		"STUDENT_LASTNAME TEXT, "
		"STUDENT_ID TEXT, "
		"STUDENT_MAJOR TEXT, "
		"STUDENT_GRADUATION TEXT);";

	// Create Instructor Table
	string tableInstructor = "CREATE TABLE IF NOT EXISTS INSTRUCTOR(" //database Instructor table
		"ID INTEGER PRIMARY KEY, "
		"NAME TEXT NOT NULL, "
		"SURNAME TEXT NOT NULL, "
		"TITLE TEXT NOT NULL,"
		"HIREYEAR INTEGER NOT NULL,"
		"DEPT TEXT NOT NULL,"
		"EMAIL TEXT NOT NULL); ";

	// Create Admin Table
	string tableADMIN = "CREATE TABLE IF NOT EXISTS ADMIN(" //database Admin table
		"ID INTEGER PRIMARY KEY, "
		"NAME TEXT NOT NULL, "
		"SURNAME TEXT NOT NULL, "
		"TITLE TEXT NOT NULL,"
		"OFFICE TEXT NOT NULL,"
		"EMAIL TEXT NOT NULL); ";

	string Logins = "CREATE TABLE LOGINS("
		"Username TEXT NOT NULL, "
		"Password TEXT NOT NULL, "
		"ID TEXT PRIMARY KEY NOT NULL, "
		"ROLE TEXT NOT NULL);";

	create_table(db, tableCourse);
	create_table(db, studentEnrolledTable);
	create_table(db, tableStudent);
	create_table(db, tableInstructor);
	create_table(db, tableADMIN);
	create_table(db, Logins);
	create_table(db, RosterTable);
}

int main()
{
	string userType;
	string user_first_name;
	string user_last_name;
	int user_ID;
	string course_add_drop;
	string course_searched;
	string course_printed;
	string user_add_remove;
	string course_search_roster;
	string course_print_roster;
	int user_input;
	string exitchoice;
	bool hasExit = false;
	bool hasExitUser = false;
	string print_schedule;
	string class_list_print;
	string student_query, instructor_query, admin_query;
	set<string> courseCatalog;
	set<string> userIDs;
	set<string> searchedCourse;
	sqlite3* db;
	sqlite3_stmt* stmt;
	int exit = 0;
	string return_v;
	char* errMsg = nullptr;
	const char* dir = "assignment3.db";
	string user_searchf, user_searchl, user_search_ID, user_search_Grad_year, user_search_Major, user_search_Email, user_search_Title, user_search_YOH, user_search_Department, user_search_Office;
	int search_user_type;
	string search_user_typestr;

	int Course_CRN;
	string department_course;
	string course_instructor;
	string course_start_time;
	int days_int;
	string Meeting_times;
	string course_semester;
	int course_year;
	int course_credits;
	string user_update_Grad_year;
	string user_update_major;
	string user_update_Title;


	string user_add_removef;
	string user_add_removel;
	int user_add_ID;
	int user_add_Grad_year;
	string user_add_Major;
	string user_add_Email;
	string user_add_Title;
	int user_add_YOH;
	string user_add_Department;
	string user_add_Office;
	int add_user_type;
	int course_add_drop_int;

	string user_removef;
	string user_removel;
	int user_remove_ID;
	int user_remove_Grad_year;
	string user_remove_Major;
	string user_remove_Email;
	string user_remove_Title;
	int user_remove_YOH;
	string user_remove_Department;
	string user_remove_Office;
	int remove_user_type;
	string course_parameter;
	exit = sqlite3_open("assignment3.db", &db);			//open the database
	create_tables(db);
	string sql(
		//main issue is that this is not being used
		"INSERT INTO COURSE VALUES(50001, 'English', 'BSEE', 'William Gibson', '8:00 AM', 'M W F', 'Fall', 2022, 4);"
		"INSERT INTO COURSE VALUES(50002, 'Math', 'HUSS', 'Reed Solomon', '10:00 AM', 'M W F', 'Winter', 2022, 4);"
		"INSERT INTO COURSE VALUES(50003, 'Science', 'BSAS', 'Isaac Asimov', '10:00 AM', 'M W F', 'Fall', 2022, 4);"
		"INSERT INTO COURSE VALUES(50004, 'Physics', 'BSCO', 'Subrahmanyan Chandrasekhar', '8:00 AM', 'M W F', 'Winter', 2022, 3);"
		"INSERT INTO COURSE VALUES(50005, 'Pyschology', 'BCOS', 'Will Wundt', '8:00 AM', 'M W F', 'Fall', 2022, 3);"
		"INSERT INTO COURSE VALUES(50006, 'Chemistry', 'BSME', 'Alfred Nobel', '7:00 PM', 'M W F', 'Winter', 2022, 2);"

		"INSERT INTO COURSE VALUES(20001, 'William', 'Gibson', 'Instructor', 1984, 'ENGL', 'Fall', 2022, 4);"
		"INSERT INTO COURSE VALUES(20002, 'Reed', 'Solomon', 'Instructor', 1960, 'TECH', 'Winter', 2022, 4);"
		"INSERT INTO COURSE VALUES(20003, 'Isaac', 'Asimov', 'Instructor', 1950, 'LITR', 'Fall', 2022, 4);"
		"INSERT INTO COURSE VALUES(20004, 'Subrahmanyan', 'Instructor', 1983, 'PHYS', 'M W F', 'Winter', 2022, 3);"
		"INSERT INTO COURSE VALUES(20005, 'Will', 'Wundt', 'Instructor', 2003, 'PSYC', 'Fall', 2022, 3);"
		"INSERT INTO COURSE VALUES(20006, 'Alfred', 'Nobel', 'Instructor', 2022, 'CHEM', 'Winter', 2022, 2);"
	);

	create_table(db, sql.c_str());
	string query = "SELECT * FROM COURSE;";

	//cout << endl << query << endl;		//print the string to screen

	// you need the callback function this time since there could be multiple rows in the table
	//sqlite3_exec(db, query.c_str(), callback, NULL, NULL);

	while (hasExit == false)
	{
		string username, password;
		int user_ID;
		cout << "\n\t<< LOGIN SYSTEM >> \n\n";
		cout << "Username: ";
		cin >> username;
		cout << "Password: ";
		cin >> password;
		cout << "ID: ";
		cin >> user_ID;

		Login loginSys(username, password, user_ID);
		string status = loginSys.authenticate();

		if (status == "valid") {
			cout << "Login successful.\n";

			sqlite3* db;
			sqlite3_stmt* stmt;
			int rc = sqlite3_open("assignment3.db", &db);
			string role_query = "SELECT ROLE FROM LOGINS WHERE Username=? AND Password=? AND ID=?;";
			rc = sqlite3_prepare_v2(db, role_query.c_str(), -1, &stmt, nullptr);

			if (rc == SQLITE_OK) {
				sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
				sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
				sqlite3_bind_int(stmt, 3, user_ID);

				rc = sqlite3_step(stmt);
				if (rc == SQLITE_ROW) {
					string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
					transform(role.begin(), role.end(), role.begin(), ::tolower);

					if (role == "student") {
						Student studentUser = Student(user_first_name, user_last_name, user_ID);
						while (hasExitUser == false) {
							cout << " 1 - Search Course \n 2 - Add Course \n 3 - Remove Course \n 4 - Print Schedule \n 0 - Exit \n";
							cin >> user_input;
							Course* CourseAttr = new Course();
							if (user_input == 1)
							{
								cout << "Do you want to search a course by a parameter? (If No, Enter no. If Yes, Enter name, crn, dep, instructor): ";
								cin >> course_parameter;
								if (course_parameter == "no") {
									return_v = studentUser.search_course(db, "", 0, "", "", course_parameter);
								}
								else if (course_parameter == "name") {
									cout << "What is the name of the Course that you want to Search?: ";
									cin >> course_add_drop;
									CourseAttr->set_title(course_add_drop);
									return_v = studentUser.search_course(db, CourseAttr->get_title(), 0, "", "", course_parameter);
								}
								else if (course_parameter == "crn") {
									cout << "What is the CRN of the Course that you want to Search?: ";
									cin >> course_add_drop_int;
									CourseAttr->set_CRN(course_add_drop_int);
									return_v = studentUser.search_course(db, "", CourseAttr->get_CRN(), "", "", course_parameter);
								}
								else if (course_parameter == "dep") {
									cout << "What is the Department of the Course that you want to Search?: ";
									cin >> course_add_drop;
									CourseAttr->set_department(course_add_drop);
									return_v = studentUser.search_course(db, "", 0, CourseAttr->get_department(), "", course_parameter);
								}
								else if (course_parameter == "instructor") {
									cout << "What is the Instructor of the Course that you want to Search?: ";
									cin >> course_add_drop;
									CourseAttr->set_instructor(course_add_drop);
									return_v = studentUser.search_course(db, "", 0, "", CourseAttr->get_instructor(), course_parameter);
								}
								if (course_parameter != "no" && course_parameter != "name" && course_parameter != "crn" && course_parameter != "dep" && course_parameter != "instructor") {
									cout << "Invalid parameter entered.\n";
								}
								else
								{
									cout << endl;

									// Prepare and execute the query to count rows
									sqlite3_stmt* stmt_check;
									int rc_check = sqlite3_prepare_v2(db, return_v.c_str(), -1, &stmt_check, nullptr);
									int row_count = 0;

									if (rc_check == SQLITE_OK) {
										while (sqlite3_step(stmt_check) == SQLITE_ROW) {
											row_count++;
										}
										sqlite3_finalize(stmt_check);
									}

									if (row_count == 0) {
										std::cout << "Course not found in the database" << std::endl;
									}
									else {
										sqlite3_exec(db, return_v.c_str(), callback, NULL, NULL);
									}
								}


							}
							else if (user_input == 2)
							{
								cout << "What is the name of the Course that you want to add?: ";
								cin >> course_add_drop;
								CourseAttr->set_title(course_add_drop);
								string check = "SELECT COUNT(*) FROM COURSE WHERE TITLE = '" + CourseAttr->get_title() + "';";
								int course_exists = 0;

								sqlite3_stmt* stmt;
								if (sqlite3_prepare_v2(db, check.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
									if (sqlite3_step(stmt) == SQLITE_ROW) {
										course_exists = sqlite3_column_int(stmt, 0);
									}
									sqlite3_finalize(stmt);
								}
								if (course_exists == 0) {
									std::cerr << "Course does not exist in the database." << endl;
								}
								else {
									return_v = studentUser.add_course(db, CourseAttr->get_title(), studentUser.get_ID());
									int rc = sqlite3_exec(db, return_v.c_str(), nullptr, nullptr, &errMsg);
									if (rc != SQLITE_OK) {
										std::cerr << "SQL error while adding course: " << errMsg << std::endl;
										sqlite3_free(errMsg);
									}
									else {
										std::cout << "Course successfully added into the database.\n";
									}
								}
							}
							else if (user_input == 3)
							{
								CourseAttr->set_title(course_add_drop);
								cout << "What is the name of the Course that you want to remove?: ";
								cin >> course_add_drop;
								CourseAttr->set_title(course_add_drop);

								string check = "SELECT COUNT(*) FROM COURSE WHERE TITLE = '" + CourseAttr->get_title() + "';";
								int course_exists = 0;

								sqlite3_stmt* stmt;
								if (sqlite3_prepare_v2(db, check.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
									if (sqlite3_step(stmt) == SQLITE_ROW) {
										course_exists = sqlite3_column_int(stmt, 0);
									}
									sqlite3_finalize(stmt);
								}
								if (course_exists == 0) {
									std::cerr << "Course does not exist in the database." << endl;
								}
								else {
									return_v = studentUser.remove_course(db, CourseAttr->get_title(), studentUser.get_ID());
									int rc = sqlite3_exec(db, return_v.c_str(), nullptr, nullptr, &errMsg);
									if (rc != SQLITE_OK) {
										std::cerr << "SQL error while deleting course: " << errMsg << std::endl;
										sqlite3_free(errMsg);
									}
									else {
										std::cout << "Course successfully removed from the database.\n";
									}
								}


							}
							else if (user_input == 4)
							{
								query = studentUser.print_schedule();
								cout << endl << query << endl;		//print the string to screen

								// you need the callback function this time since there could be multiple rows in the table
								sqlite3_exec(db, query.c_str(), callback, NULL, NULL);
							}
							else if (user_input == 0)
							{
								hasExitUser = true;
							}
						}
					}
					else if (role == "instructor") {
						Instructor instructorUser = Instructor(user_first_name, user_last_name, user_ID);
						while (hasExitUser == false) {
							cout << " 1 - Print Schedule \n 2 - Print Class List for a Student \n 3 - Print Course Roster \n 4 - Search Course \n 0 - Exit \n";
							cin >> user_input;
							Course* CourseAttr = new Course();
							if (user_input == 1)
							{
								query = instructorUser.print_schedule(instructorUser.get_first_name(), instructorUser.get_last_name());
								cout << endl << query << endl;		//print the string to screen

								// you need the callback function this time since there could be multiple rows in the table
								sqlite3_exec(db, query.c_str(), callback, NULL, NULL);
							}
							else if (user_input == 2)
							{
								int student_id;
								Student* tmp_student = new Student();
								cout << "Enter Student ID to view their class list: ";
								cin >> student_id;
								tmp_student->set_ID(student_id);
								string name_query = instructorUser.get_studentname(tmp_student->get_ID());
								sqlite3_stmt* stmt_name = nullptr;

								if (sqlite3_prepare_v2(db, name_query.c_str(), -1, &stmt_name, nullptr) == SQLITE_OK) {
									if (sqlite3_step(stmt_name) == SQLITE_ROW) {
										tmp_student->set_firstname(reinterpret_cast<const char*>(sqlite3_column_text(stmt_name, 0)));
										tmp_student->set_lastname(reinterpret_cast<const char*>(sqlite3_column_text(stmt_name, 1)));
										cout << "First Name = " << tmp_student->get_firstname() << "   |   Last Name = " << tmp_student->get_lastname() << "\n";
									}
									else {
										std::cerr << "Student ID not found.\n";
										sqlite3_finalize(stmt_name);
										continue;
									}
									sqlite3_finalize(stmt_name);
								}
								else {
									std::cerr << "Failed to prepare name query. Error: " << sqlite3_errmsg(db) << "\n";
									continue;
								}
								string student_query = instructorUser.getstudent_classlist(tmp_student->get_ID());
								cout << "\nCourses enrolled:\n";
								char* errMsg = nullptr;
								int rc = sqlite3_exec(db, student_query.c_str(), callback, NULL, &errMsg);
								if (rc != SQLITE_OK) {
									std::cerr << "SQL error (Student Courses): " << errMsg << std::endl;
									sqlite3_free(errMsg);
								}
							}
							else if (user_input == 3)
							{
								string title;
								cout << "Enter the name of the course to view its roster: ";
								cin >> title;
								string course_info = instructorUser.get_courseinfo(title);
								sqlite3_stmt* stmt_header = nullptr;

								if (sqlite3_prepare_v2(db, course_info.c_str(), -1, &stmt_header, nullptr) == SQLITE_OK) {
									if (sqlite3_step(stmt_header) == SQLITE_ROW) {
										CourseAttr->set_title(reinterpret_cast<const char*>(sqlite3_column_text(stmt_header, 0)));
										CourseAttr->set_instructor(reinterpret_cast<const char*>(sqlite3_column_text(stmt_header, 1)));
										CourseAttr->set_CRN(sqlite3_column_int(stmt_header, 2));
										cout << "COURSE: " << CourseAttr->get_title() << "   | INSTRUCTOR: " << CourseAttr->get_instructor() << "   | CRN: " << CourseAttr->get_CRN() << "\n\n";
									}
									else {
										std::cerr << "Course not found.\n";
										sqlite3_finalize(stmt_header);
										continue;
									}
									sqlite3_finalize(stmt_header);
								}
								else {
									std::cerr << "Failed to prepare course header query. Error: " << sqlite3_errmsg(db) << "\n";
									continue;
								}
								string roster_info = instructorUser.getcourse_roster(title);
								cout << "Enrolled Students:\n";
								char* errMsg = nullptr;
								int rc = sqlite3_exec(db, roster_info.c_str(), callback, NULL, &errMsg);
								if (rc != SQLITE_OK) {
									std::cerr << "SQL error (Course Roster): " << errMsg << std::endl;
									sqlite3_free(errMsg);
								}
							}
							else if (user_input == 4)
							{
								cout << "Do you want to search a course by a parameter? (If No, Enter no. If Yes, Enter name, crn, dep, instructor): ";
								cin >> course_parameter;
								if (course_parameter == "no") {
									return_v = instructorUser.search_course(db, "", 0, "", "", course_parameter);
								}
								else if (course_parameter == "name") {
									cout << "What is the name of the Course that you want to Search?: ";
									cin >> course_add_drop;
									CourseAttr->set_title(course_add_drop);
									return_v = instructorUser.search_course(db, CourseAttr->get_title(), 0, "", "", course_parameter);
								}
								else if (course_parameter == "crn") {
									cout << "What is the CRN of the Course that you want to Search?: ";
									cin >> course_add_drop_int;
									CourseAttr->set_CRN(course_add_drop_int);
									return_v = instructorUser.search_course(db, "", CourseAttr->get_CRN(), "", "", course_parameter);
								}
								else if (course_parameter == "dep") {
									cout << "What is the Department of the Course that you want to Search?: ";
									cin >> course_add_drop;
									CourseAttr->set_department(course_add_drop);
									return_v = instructorUser.search_course(db, "", 0, CourseAttr->get_department(), "", course_parameter);
								}
								else if (course_parameter == "instructor") {
									cout << "What is the Instructor of the Course that you want to Search?: ";
									cin >> course_add_drop;
									CourseAttr->set_instructor(course_add_drop);
									return_v = instructorUser.search_course(db, "", 0, "", CourseAttr->get_instructor(), course_parameter);
								}
								if (course_parameter != "no" && course_parameter != "name" && course_parameter != "crn" && course_parameter != "dep" && course_parameter != "instructor") {
									cout << "Invalid parameter entered.\n";
								}
								else
								{
									cout << endl;
									sqlite3_stmt* stmt_check;
									int rc_check = sqlite3_prepare_v2(db, return_v.c_str(), -1, &stmt_check, nullptr);
									int row_count = 0;

									if (rc_check == SQLITE_OK) {
										while (sqlite3_step(stmt_check) == SQLITE_ROW) {
											row_count++;
										}
										sqlite3_finalize(stmt_check);
									}

									if (row_count == 0) {
										std::cout << "Course not found in the database" << std::endl;
									}
									else {
										sqlite3_exec(db, return_v.c_str(), callback, NULL, NULL);
									}
								}
							}
							else if (user_input == 0)
							{
								hasExitUser = true;
							}
						}
					}
					else if (role == "admin") {
						Admin adminUser = Admin(user_first_name, user_last_name, user_ID);
						while (hasExitUser == false) {
							cout << " 1 - Add Course \n 2 - Remove Course \n 3 - Add User \n 4 - Remove User \n 5 - Update User \n 6 - Search Roster \n 7 - Print Roster \n 8 - Search Course \n 9 - Print Course \n 0 - Exit \n";
							cin >> user_input;
							Course* CourseAttr = new Course();
							if (user_input == 1)
							{
								cout << "What is the name of the Course that you want to add?: ";
								cin >> course_add_drop;
								//std::transform(course_add_drop.begin(), course_add_drop.end(), course_add_drop.begin(), ::toupper);
								cout << "What is the CRN of the Course that you want to add?: ";
								cin >> Course_CRN;
								cout << "What Department does the course belong to?: ";
								cin >> department_course;
								std::cin.ignore();
								cout << "Who is the Instructor of the course?: ";
								std::getline(cin, course_instructor);
								//cin >> course_instructor;
								cout << "What Time does the class start(Enter: XX:XX AM/PM)?: ";
								std::getline(cin, course_start_time);
								//cin >> course_start_time;
								cout << "On which days is the classes attended?: \n 1 - M W F \n 2 - T TH \n 3 - M W \n";
								cin >> days_int;
								if (days_int == 1) { Meeting_times = "M W F"; }
								else if (days_int == 2) { Meeting_times = "T TH"; }
								else if (days_int == 3) { Meeting_times = "M W"; }
								cout << "Which Semester is the course taught?: ";
								cin >> course_semester;
								cout << "Which year is the course taught?: ";
								cin >> course_year;
								cout << "How many credits is the course worth?: ";
								cin >> course_credits;
								Course* CourseAttr = new Course((int)Course_CRN, course_add_drop, department_course, course_instructor, course_start_time, Meeting_times, course_semester, (int)course_year, (int)course_credits);
								return_v = adminUser.add_course(CourseAttr->get_title(), CourseAttr->get_CRN(), CourseAttr->get_department(), CourseAttr->get_instructor(), CourseAttr->get_time(), CourseAttr->get_days(), CourseAttr->get_semester(), CourseAttr->get_year(), CourseAttr->get_credits());
								int rc = sqlite3_exec(db, return_v.c_str(), nullptr, nullptr, &errMsg);
								if (rc != SQLITE_OK) {
									std::cerr << "SQL error while adding course: " << errMsg << std::endl;
									sqlite3_free(errMsg);
								}
								else {
									std::cout << "Course successfully added into the database.\n";
								}
							}
							else if (user_input == 2)
							{
								cout << "What is the name of the Course that you want to remove?: ";
								cin >> course_add_drop;
								//std::transform(course_add_drop.begin(), course_add_drop.end(), course_add_drop.begin(), ::toupper);
								cout << "What is the CRN of the Course that you want to remove?: ";
								cin >> Course_CRN;
								cout << "What Department does the course belong to?: ";
								cin >> department_course;
								std::cin.ignore();
								cout << "Who is the Instructor of the course?: ";
								std::getline(cin, course_instructor);
								//cin >> course_instructor;
								cout << "What Time does the class start(Enter: XX:XX AM/PM)?: ";
								std::getline(cin, course_start_time);
								//cin >> course_start_time;
								cout << "On which days is the classes attended?: \n 1 - M W F \n 2 - T TH \n 3 - M W \n";
								cin >> days_int;
								if (days_int == 1) { Meeting_times = "M W F"; }
								else if (days_int == 2) { Meeting_times = "T TH"; }
								else if (days_int == 3) { Meeting_times = "M W"; }
								cout << "Which Semester is the course taught?: ";
								cin >> course_semester;
								cout << "Which year is the course taught?: ";
								cin >> course_year;
								cout << "How many credits is the course worth?: ";
								cin >> course_credits;
								Course* CourseAttr = new Course((int)Course_CRN, course_add_drop, department_course, course_instructor, course_start_time, Meeting_times, course_semester, (int)course_year, (int)course_credits);
								return_v = adminUser.remove_course(CourseAttr->get_title(), CourseAttr->get_CRN(), CourseAttr->get_department(), CourseAttr->get_instructor(), CourseAttr->get_time(), CourseAttr->get_days(), CourseAttr->get_semester(), CourseAttr->get_year(), CourseAttr->get_credits());
								int rc = sqlite3_exec(db, return_v.c_str(), nullptr, nullptr, &errMsg);
								if (rc != SQLITE_OK) {
									std::cerr << "SQL error while deleting course: " << errMsg << std::endl;
									sqlite3_free(errMsg);
								}
								else {
									std::cout << "Course successfully removed from the database.\n";
								}
							}
							else if (user_input == 3)
							{
								cout << "What is the first name of the user that you want to add?: ";
								cin >> user_add_removef;
								cout << "What is the last name of the user that you want to add?: ";
								cin >> user_add_removel;
								cout << "User's ID?: ";
								cin >> user_add_ID;
								cout << "User's Email?: ";
								cin >> user_add_Email;
								cout << "User Type: \n 1 - Student \n 2 - Instructor \n 3 - Administrator \n";
								cin >> add_user_type;
								if (add_user_type == 1) {
									cout << "Student's Graduation Year?: ";
									cin >> user_add_Grad_year;
									cout << "Student's Major?: ";
									cin >> user_add_Major;
									Student* Studenttemp = new Student(user_add_removef, user_add_removel, user_add_ID, user_add_Email, user_add_Grad_year, user_add_Major);
									return_v = adminUser.add_user(user_add_removef, user_add_removel, user_add_ID, user_add_Grad_year, user_add_Major, user_add_Email, 1, "", 0, "", "");
								}
								else if (add_user_type == 2) {
									cout << "Instructor's Title?: ";
									cin >> user_add_Title;
									cout << "Instructor's Year of Hire?: ";
									cin >> user_add_YOH;
									cout << "Instructor's Department?: ";
									cin >> user_add_Department;
									Instructor* Instructortemp = new Instructor(user_add_removef, user_add_removel, user_add_ID, user_add_Email, user_add_Title, user_add_YOH, user_add_Department);
									return_v = adminUser.add_user(user_add_removef, user_add_removel, user_add_ID, 0, "", user_add_Email, 2, user_add_Title, user_add_YOH, user_add_Department, "");
								}
								else if (add_user_type == 3) {
									cout << "Admin's Title?: ";
									cin >> user_add_Title;
									std::cin.ignore();
									cout << "Admin's Office?: ";
									std::getline(cin, user_add_Office);
									Admin* Admintemp = new Admin(user_add_removef, user_add_removel, user_add_ID, user_add_Email, user_add_Title, user_add_Office);
									return_v = adminUser.add_user(user_add_removef, user_add_removel, user_add_ID, 0, "", user_add_Email, 3, user_add_Title, 0, "", user_add_Office);
								}
								//return_v = adminUser.add_user(user_add_removef, user_add_removel, user_add_ID, user_add_Grad_year, user_add_Major, user_add_Email, add_user_type, user_add_Title, user_add_YOH, user_add_Department, user_add_Office);
								int rc = sqlite3_exec(db, return_v.c_str(), nullptr, nullptr, &errMsg);
								if (rc != SQLITE_OK) {
									std::cerr << "SQL error: " << errMsg << std::endl;
									sqlite3_free(errMsg);
								}
								else {
									std::cout << "New user successfully added into database.\n";
								}
							}
							else if (user_input == 4)
							{
								cout << "What is the first name of the user that you want to remove?: ";
								cin >> user_removef;
								cout << "What is the last name of the user that you want to add?: ";
								cin >> user_removel;
								cout << "User's ID?: ";
								cin >> user_remove_ID;
								cout << "User's Email?: ";
								cin >> user_remove_Email;
								cout << "User Type: \n 1 - Student \n 2 - Instructor \n 3 - Administrator \n";
								cin >> remove_user_type;
								if (remove_user_type == 1) {
									cout << "User's Graduation Year?: ";
									cin >> user_remove_Grad_year;
									cout << "User's Major?: ";
									cin >> user_remove_Major;
									Student* Studenttemp = new Student(user_removef, user_removel, user_remove_ID, user_remove_Email, user_remove_Grad_year, user_remove_Major);
									return_v = adminUser.remove_user(Studenttemp->get_firstname(), Studenttemp->get_lastname(), Studenttemp->get_ID(), Studenttemp->get_gradYear(), Studenttemp->get_major(), Studenttemp->get_email(), 1, "", 0, "", "");
								}
								else if (remove_user_type == 2) {
									cin.ignore();
									cout << "Instructor's Title?: ";
									getline(cin, user_remove_Title);
									cout << "Instructor's Year of Hire?: ";
									cin >> user_remove_YOH;
									cout << "Instructor's Department?: ";
									cin >> user_remove_Department;
									Instructor* Instructortemp = new Instructor(user_removef, user_removel, user_remove_ID, user_remove_Email, user_remove_Title, user_remove_YOH, user_remove_Department);
									return_v = adminUser.remove_user(Instructortemp->get_firstname(), Instructortemp->get_lastname(), Instructortemp->get_ID(), 0, "", Instructortemp->get_email(), 2, Instructortemp->get_title(), Instructortemp->get_YOH(), Instructortemp->get_Department(), "");
								}
								else if (remove_user_type == 3) {
									cout << "Admin's Title?: ";
									cin >> user_remove_Title;
									std::cin.ignore();
									cout << "Admin's Office?: ";
									std::getline(cin, user_remove_Office);
									Admin* Admintemp = new Admin(user_removef, user_removel, user_remove_ID, user_remove_Email, user_remove_Title, user_remove_Office);
									return_v = adminUser.remove_user(Admintemp->get_firstname(), Admintemp->get_lastname(), Admintemp->get_ID(), 0, "", Admintemp->get_email(), 3, Admintemp->get_title(), 0, "", Admintemp->get_office());
								}
								//return_v = adminUser.remove_user(user_removef, user_removel, user_remove_ID, user_remove_Grad_year, user_remove_Major, user_remove_Email, remove_user_type, user_remove_Title, user_remove_YOH, user_remove_Department, user_remove_Office);
								int rc = sqlite3_exec(db, return_v.c_str(), nullptr, nullptr, &errMsg);
								if (rc != SQLITE_OK) {
									std::cerr << "SQL error: " << errMsg << std::endl;
									sqlite3_free(errMsg);
								}
								else {
									std::cout << "New user successfully removed from the database!\n";
								}
								user_input == 11;
							}
							//else if (user_input == 5)
							//{
							//	cout << "Which student do you want to add?: ";
							//	cin >> user_add_remove;
							//	cout << "Which course do you want to add them to?: ";
							//	cin >> course_add_drop;
							//	adminUser.add_student_course(user_add_remove, course_add_drop);
							//}
							//else if (user_input == 6)
							//{
							//	cout << "Which student do you want to remove?: ";
							//	cin >> user_add_remove;
							//	cout << "Which course do you want to remove them from?: ";
							//	cin >> course_add_drop;
							//	adminUser.remove_student_course(user_add_remove, course_add_drop);
							//}
							else if (user_input == 5) {
								cout << "What is the first name of the user that you want to update?: ";
								cin >> user_searchf;
								cout << "What is the last name of the user that you want to update?: ";
								cin >> user_searchl;
								cout << "User's ID?: ";
								cin >> user_search_ID;
								cout << "User's Email?: ";
								cin >> user_search_Email;
								cout << "User Type: \n 1 - Student \n 2 - Instructor \n 3 - Administrator \n";
								cin >> search_user_type;
								if (search_user_type == 1) {
									cout << "User's Graduation Year?: ";
									cin >> user_search_Grad_year;
									cout << "What do you want to update their graduation year to?: ";
									cin >> user_update_Grad_year;
									cout << "User's Major?: ";
									cin >> user_search_Major;
									cout << "What do you want to update their major to?: ";
									cin >> user_update_major;
								}
								else if (search_user_type == 2) {
									cout << "Instructor's Title?: ";
									cin >> user_search_Title;
									cout << "What do you want to update their Title to?: ";
									getline(cin, user_update_Title);
									cout << "Instructor's Year of Hire?: ";
									cin >> user_search_YOH;
									cout << "Instructor's Department?: ";
									cin >> user_search_Department;
								}
								else if (search_user_type == 3) {
									cout << "Admin's Title?: ";
									cin >> user_add_Title;
									cin.ignore();
									cout << "What do you want to update their Title to?: ";
									getline(cin, user_update_Title);
									//std::cin.ignore();
									cout << "Admin's Office?: ";
									std::getline(cin, user_add_Office);
								}
								return_v = adminUser.update_user(db, user_searchf, user_searchl, user_search_ID, user_search_Grad_year, user_update_Grad_year, user_search_Major, user_update_major, user_search_Email, search_user_type, user_search_Title, user_update_Title, user_search_YOH, user_search_Department, user_add_Office);
								int rc = sqlite3_exec(db, return_v.c_str(), nullptr, nullptr, &errMsg);
								if (rc != SQLITE_OK) {
									std::cerr << "SQL error: " << errMsg << std::endl;
									sqlite3_free(errMsg);
								}
								else {
									std::cout << "New user successfully updated in database.\n";
								}
							}
							else if (user_input == 6)
							{
								cout << "What is the first name of the user that you want to Search?: ";
								cin >> user_searchf;
								cout << "What is the last name of the user that you want to Search?: ";
								cin >> user_searchl;
								cout << "User's ID?: ";
								cin >> user_search_ID;
								cout << "User's Email?: ";
								cin >> user_search_Email;
								cout << "User Type: \n 1 - Student \n 2 - Instructor \n 3 - Administrator \n";
								cin >> search_user_type;
								if (search_user_type == 1) { search_user_typestr = "STUDENT"; }
								else if (search_user_type == 2) { search_user_typestr = "INSTRUCTOR"; }
								else if (search_user_type == 3) { search_user_typestr = "ADMIN"; }
								if (search_user_type == 1) {
									cout << "User's Graduation Year?: ";
									cin >> user_search_Grad_year;
									cout << "User's Major?: ";
									cin >> user_search_Major;
								}
								else if (search_user_type == 2) {
									cout << "Instructor's Title?: ";
									cin >> user_search_Title;
									cout << "Instructor's Year of Hire?: ";
									cin >> user_search_YOH;
									cout << "Instructor's Department?: ";
									cin >> user_search_Department;
								}
								else if (search_user_type == 3) {
									cout << "Admin's Title?: ";
									cin >> user_search_Title;
									cout << "Admin's Office?: ";
									cin >> user_search_Office;
								}
								adminUser.search_roster(db, user_searchf, user_searchl, user_search_ID, user_search_Grad_year, user_search_Major, user_search_Email, search_user_typestr, user_search_Title, user_search_YOH, user_search_Department, user_search_Office);
							}
							else if (user_input == 7)
							{
								adminUser.print_roster(student_query, instructor_query, admin_query);

								char* errMsg = nullptr;
								int rc;
								int rc1;
								int rc2;
								cout << endl << student_query << endl;
								rc = sqlite3_exec(db, student_query.c_str(), callback, NULL, NULL);
								if (rc != SQLITE_OK) {
									std::cerr << "SQL error (Student): " << errMsg << std::endl;
									sqlite3_free(errMsg);
								}
								cout << endl << instructor_query << endl;
								rc1 = sqlite3_exec(db, instructor_query.c_str(), callback, NULL, &errMsg);
								if (rc != SQLITE_OK) {
									std::cerr << "SQL error (Instructor): " << errMsg << std::endl;
									sqlite3_free(errMsg);
								}
								cout << endl << admin_query << endl;
								rc2 = sqlite3_exec(db, admin_query.c_str(), callback, NULL, &errMsg);
								if (rc != SQLITE_OK) {
									std::cerr << "SQL error (Admin): " << errMsg << std::endl;
									sqlite3_free(errMsg);
								}
							}
							else if (user_input == 8)
							{
								cout << "Do you want to search a course by a parameter? (If No, Enter no. If Yes, Enter name, crn, dep, instructor): ";
								cin >> course_parameter;
								if (course_parameter == "no") {
									return_v = adminUser.search_course(db, "", 0, "", "", course_parameter);
								}
								else if (course_parameter == "name") {
									cout << "What is the name of the Course that you want to Search?: ";
									cin >> course_add_drop;
									CourseAttr->set_title(course_add_drop);
									return_v = adminUser.search_course(db, CourseAttr->get_title(), 0, "", "", course_parameter);
								}
								else if (course_parameter == "crn") {
									cout << "What is the CRN of the Course that you want to Search?: ";
									cin >> course_add_drop_int;
									CourseAttr->set_CRN(course_add_drop_int);
									return_v = adminUser.search_course(db, "", CourseAttr->get_CRN(), "", "", course_parameter);
								}
								else if (course_parameter == "dep") {
									cout << "What is the Department of the Course that you want to Search?: ";
									cin >> course_add_drop;
									CourseAttr->set_department(course_add_drop);
									return_v = adminUser.search_course(db, "", 0, CourseAttr->get_department(), "", course_parameter);
								}
								else if (course_parameter == "instructor") {
									cout << "What is the Instructor of the Course that you want to Search?: ";
									cin >> course_add_drop;
									CourseAttr->set_instructor(course_add_drop);
									return_v = adminUser.search_course(db, "", 0, "", CourseAttr->get_instructor(), course_parameter);
								}
								if (course_parameter != "no" && course_parameter != "name" && course_parameter != "crn" && course_parameter != "dep" && course_parameter != "instructor") {
									cout << "Invalid parameter entered.\n";
								}
								else
								{
									cout << endl;
									sqlite3_stmt* stmt_check;
									int rc_check = sqlite3_prepare_v2(db, return_v.c_str(), -1, &stmt_check, nullptr);
									int row_count = 0;

									if (rc_check == SQLITE_OK) {
										while (sqlite3_step(stmt_check) == SQLITE_ROW) {
											row_count++;
										}
										sqlite3_finalize(stmt_check);
									}

									if (row_count == 0) {
										std::cout << "Course not found in the database" << std::endl;
									}
									else {
										sqlite3_exec(db, return_v.c_str(), callback, NULL, NULL);
									}
								}
							}
							else if (user_input == 9)
							{
								cout << "What course do you want to print?: ";
								cin >> course_printed;
								query = adminUser.print_courses(course_printed);
								cout << endl << query << endl;		//print the string to screen

								// you need the callback function this time since there could be multiple rows in the table
								sqlite3_exec(db, query.c_str(), callback, NULL, NULL);
							}
							else if (user_input == 0)
							{
								hasExitUser = true;
							}
							//std::string sql = return_v; // Returns SQL INSERT string
							//sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
						}
					}
				}
			}

			sqlite3_finalize(stmt);
			sqlite3_close(db);
		}
		else {
			cout << "Login failed. Would you like to register? (yes/no): ";
			string choice;
			cin >> choice;
			transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
			if (choice == "yes") {
				string new_username;
				string new_password;
				string role;
				Login* newUser = new Login();
				int new_id;
				cout << "Enter new username: ";
				cin >> new_username;
				newUser->setUsername(new_username);
				cout << "Enter new password: ";
				cin >> new_password;
				newUser->setPassword(new_password);
				cout << "Enter your ID: ";
				cin >> new_id;
				newUser->setID(new_id);
				cout << "Enter your role (Student, Instructor, Admin): ";
				cin >> role;
				transform(role.begin(), role.end(), role.begin(), ::toupper);
				newUser->setRole(role);
				newUser->registerUser(newUser->getUsername(), newUser->getPassword(), newUser->getID(), newUser->getRole());
				Admin* adminUser = new Admin("admin", "account", 0);  // dummy Admin instance
				string email;
				string user_add_Title;
				int user_add_YOH;
				string user_add_Department;
				string user_add_Office;
				string newUser_Grad_year, newUser_Major;

				string user_insert;

				if (role == "STUDENT") {
					Student* studentUser = new Student("Student", "account", 0);  // dummy Admin instance
					cout << "Enter First Name: ";
					cin >> user_first_name;
					studentUser->set_firstname(user_first_name);
					cout << "Enter Last Name: ";
					cin >> user_last_name;
					studentUser->set_lastname(user_last_name);
					cout << "Enter Email: ";
					cin >> email;
					studentUser->set_email(email);
					studentUser->set_lastname(user_last_name);
					cout << "Enter Graduation Year: ";
					cin >> newUser_Grad_year;
					cout << "Enter Major: ";
					cin >> newUser_Major;

					user_insert = adminUser->add_user(
						studentUser->get_firstname(), studentUser->get_lastname(), newUser->getID(),
						studentUser->get_gradYear(), studentUser->get_major(), studentUser->get_email(),
						1, "", 0, "", "");  // role = 1 for student
				}
				else if (role == "INSTRUCTOR") {
					Instructor* instructorUser = new Instructor("Instructor", "account", 0);  // dummy Instructor instance
					cout << "Enter First Name: ";
					cin >> user_first_name;
					instructorUser->set_firstname(user_first_name);
					cout << "Enter Last Name: ";
					cin >> user_last_name;
					instructorUser->set_lastname(user_last_name);
					cout << "Enter Email: ";
					cin >> email;
					instructorUser->set_email(email);
					cout << "Enter Title (e.g., Professor): ";
					cin >> user_add_Title;
					instructorUser->set_title(user_add_Title);
					cout << "Enter Hire Year: ";
					cin >> user_add_YOH;
					instructorUser->set_YOH(user_add_YOH);
					cout << "Enter Department: ";
					cin >> user_add_Department;
					instructorUser->set_Department(user_add_Department);

					user_insert = adminUser->add_user(
						instructorUser->get_firstname(), instructorUser->get_lastname(), newUser->getID(),
						0, "", instructorUser->get_email(),
						2, instructorUser->get_title(), instructorUser->get_YOH(), instructorUser->get_Department(), "");  // role = 2
				}
				else if (role == "ADMIN") {
					cout << "Enter First Name: ";
					cin >> user_first_name;
					adminUser->set_firstname(user_first_name);
					cout << "Enter Last Name: ";
					cin >> user_last_name;
					adminUser->set_lastname(user_last_name);
					cout << "Enter Email: ";
					cin >> email;
					adminUser->set_email(email);
					cout << "Enter Title (e.g., System Admin): ";
					cin >> user_add_Title;
					adminUser->set_title(user_add_Title);
					cin.ignore();
					cout << "Enter Office: ";
					getline(cin, user_add_Office);
					adminUser->set_office(user_add_Office);
					user_insert = adminUser->add_user(
						adminUser->get_firstname(), adminUser->get_lastname(), newUser->getID(),
						0, "", adminUser->get_email(),
						3, adminUser->get_title(), 0, "", adminUser->get_office());  // role = 3
				}
				/*else {
					cout << "Invalid role. Registration aborted.\n";
					return;
				}*/

				int rc = sqlite3_exec(db, user_insert.c_str(), nullptr, nullptr, &errMsg);
				if (rc != SQLITE_OK) {
					std::cerr << "Error inserting into role table: " << errMsg << endl;
					sqlite3_free(errMsg);
				}
				else {
					cout << role << " registered successfully.\n";
				}
			}
		}

		cout << "Would you like to exit the program? (yes/no): ";
		string exitchoice;
		cin >> exitchoice;
		transform(exitchoice.begin(), exitchoice.end(), exitchoice.begin(), ::tolower);
		if (exitchoice == "yes") {
			hasExit = true;
		}
		// Reset all critical variables used in program
			userType = "";
			user_first_name = "";
			user_last_name = "";
			user_ID = 0;
			course_add_drop = "";
			course_searched = "";
			course_printed = "";
			user_add_remove = "";
			user_add_remove = "";
			course_search_roster = "";
			course_print_roster = "";
			user_input = 100;
			exitchoice = "";
			hasExitUser = false;
			print_schedule = "";
			class_list_print = "";
			if (exitchoice == "yes")
				hasExit = true;
			else
				hasExit = false;
	}
	return 0;
}	
