
#include <iostream>
#include <algorithm>
#include <set>
#include "User.h"
#include "Student.h"
#include "Instructor.h"
#include "Admin.h"
extern "C" {
	#include "sqlite3.h"
}
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::set;

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
int main()
{
	string userType;
	string user_first_name;
	string user_last_name;
	string user_ID;
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


	string user_add_removef;
	string user_add_removel;
	string user_add_ID;
	string user_add_Grad_year;
	string user_add_Major;
	string user_add_Email;
	string user_add_Title;
	string user_add_YOH;
	string user_add_Department;
	string user_add_Office;
	int add_user_type;


	string user_removef;
	string user_removel;
	string user_remove_ID;
	string user_remove_Grad_year;
	string user_remove_Major;
	string user_remove_Email;
	string user_remove_Title;
	string user_remove_YOH;
	string user_remove_Department;
	string user_remove_Office;
	int remove_user_type;

	string tableADMIN = "CREATE TABLE IF NOT EXISTS ADMIN(" //database Admin table
		"ID INTEGER PRIMARY KEY, "
		"NAME TEXT NOT NULL, "
		"SURNAME TEXT NOT NULL, "
		"TITLE TEXT NOT NULL,"
		"OFFICE TEXT NOT NULL,"
		"EMAIL TEXT NOT NULL); ";

	exit = sqlite3_open("assignment3.db", &db);			//open the database

	char* messageError;

	exit = sqlite3_exec(db, tableADMIN.c_str(), nullptr, nullptr, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Create Table" << std::endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Table created Successfully" << std::endl;

	string tableInstructor = "CREATE TABLE IF NOT EXISTS INSTRUCTOR(" //database Instructor table
		"ID INTEGER PRIMARY KEY, "
		"NAME TEXT NOT NULL, "
		"SURNAME TEXT NOT NULL, "
		"TITLE TEXT NOT NULL,"
		"HIREYEAR INTEGER NOT NULL,"
		"DEPT TEXT NOT NULL,"
		"EMAIL TEXT NOT NULL); ";

	exit = sqlite3_exec(db, tableInstructor.c_str(), nullptr, nullptr, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Create Table" << std::endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Table created Successfully" << std::endl;

	string tableStudent = "CREATE TABLE IF NOT EXISTS STUDENT("  //database Student table
		"ID INTEGER PRIMARY KEY, "
		"NAME TEXT NOT NULL, "
		"SURNAME TEXT NOT NULL, "
		"GRADYEAR INTEGER NOT NULL,"
		"MAJOR TEXT NOT NULL,"
		"EMAIL TEXT NOT NULL); ";

	exit = sqlite3_exec(db, tableStudent.c_str(), nullptr, nullptr, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Create Table" << std::endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Table created Successfully" << std::endl;

	string tableCourse = "CREATE TABLE IF NOT EXISTS COURSE(" //database Course table
		"CRN INTEGER PRIMARY KEY, "
		"TITLE TEXT NOT NULL, "
		"DEPARTMENT TEXT NOT NULL, "
		"INSTRUCTOR TEXT NOT NULL, "
		"TIME TEXT NOT NULL,"
		"DofW TEXT NOT NULL,"
		"SEMESTER TEXT NOT NULL,"
		"YEAR INTEGER NOT NULL,"
		"CREDITS INTEGER NOT NULL); ";

	exit = sqlite3_exec(db, tableCourse.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Create Table" << std::endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Table created Successfully" << std::endl;

	//Admin, Instructor, Student addition (as backup)
	//Create Course List (yes I stopped caring at this point)

	/*
	string sql("INSERT INTO ADMIN VALUES(30001, 'Margaret', 'Hamilton', 'President', 'Dobbs 1600', 'hamiltonm');"
		"INSERT INTO ADMIN VALUES(30002, 'Vera', 'Rubin', 'Registar', 'Wentworth 101', 'rubinv');"

		"INSERT INTO INSTRUCTOR VALUES(20001, 'Joseph', 'Fourier', 'Full Prof.', 1820, 'BSEE', 'fourierj');"
		"INSERT INTO INSTRUCTOR VALUES(20002, 'Nelson', 'Patrick', 'Full Prof.', 1994, 'HUSS', 'patrickn');"
		"INSERT INTO INSTRUCTOR VALUES(20003, 'Galileo', 'Galilei', 'Full Prof.', 1600, 'BSAS', 'galileig');"
		"INSERT INTO INSTRUCTOR VALUES(20004, 'Alan', 'Turing', 'Associate Prof.', 1940, 'BSCO', 'turinga');"
		"INSERT INTO INSTRUCTOR VALUES(20005, 'Katie', 'Bouman', 'Associate Prof.', 2019, 'BCOS', 'boumank');"
		"INSERT INTO INSTRUCTOR VALUES(20006, 'Daniel', 'Bernouli', 'Associate Prof.', 1760, 'BSME', 'bernoulid');"

		"INSERT INTO STUDENT VALUES(10001, 'Isaac', 'Newton', 1668, 'BSAS', 'newtoni');"
		"INSERT INTO STUDENT VALUES(10002, 'Marie', 'Curie', 1903, 'BSAS', 'curiem');"
		"INSERT INTO STUDENT VALUES(10003, 'Nikola', 'Tesla', 1878, 'BSEE', 'teslan');"
		"INSERT INTO STUDENT VALUES(10004, 'Thomas', 'Edison', 1879, 'BSEE', 'edisont');"
		"INSERT INTO STUDENT VALUES(10005, 'John', 'von Neumann', 1923, 'BSCO', 'vonneumanj');"
		"INSERT INTO STUDENT VALUES(10006, 'Grace', 'Hopper', 1928, 'BCOS', 'hopperg');"
		"INSERT INTO STUDENT VALUES(10007, 'Mae', 'Jemison', 1981, 'BSCH', 'jamisonm');"
		"INSERT INTO STUDENT VALUES(10008, 'Mark', 'Dean', 1979, 'BSCO', 'deanm');"
		"INSERT INTO STUDENT VALUES(10009, 'Michael', 'Faraday', 1812, 'BSAS', 'faradaym');"
		"INSERT INTO STUDENT VALUES(10010, 'Ada', 'Lovelace', 1832, 'BCOS', 'lovelacea');"

		//main issue is that this is not being used
		"INSERT INTO COURSE VALUES(50001, 'Engrish', 'BSEE', '8:00 AM', 'M W F', 'Fall', 2022, 4);"
		"INSERT INTO COURSE VALUES(50002, 'Matting', 'HUSS', '10:00 AM', 'M W F', 'Winter', 2022, 4);"
		"INSERT INTO COURSE VALUES(50003, 'Blow Ups', 'BSAS', '10:00 AM', 'M W F', 'Fall', 2022, 4);"
		"INSERT INTO COURSE VALUES(50004, 'Torture Rooms', 'BSCO', '8:00 AM', 'M W F', 'Winter', 2022, 3);"
		"INSERT INTO COURSE VALUES(50005, 'Femboyant Architypes', 'BCOS', '8:00 AM', 'M W F', 'Fall', 2022, 3);"
		"INSERT INTO COURSE VALUES(50006, 'Eric Femboy Crisis Hotline', 'BSME', '7:00 PM', 'M W F', 'Winter', 2022, 2);"
	);
	*/

	string sql(
		//main issue is that this is not being used
		"INSERT INTO COURSE VALUES(50001, 'English', 'BSEE', 'William Gibson', '8:00 AM', 'M W F', 'Fall', 2022, 4);"
		"INSERT INTO COURSE VALUES(50002, 'Math', 'HUSS', 'Reed-Solomon', '10:00 AM', 'M W F', 'Winter', 2022, 4);"
		"INSERT INTO COURSE VALUES(50003, 'Science', 'BSAS', 'Isaac Asimov', '10:00 AM', 'M W F', 'Fall', 2022, 4);"
		"INSERT INTO COURSE VALUES(50004, 'Physics', 'BSCO', 'Subrahmanyan Chandrasekhar', '8:00 AM', 'M W F', 'Winter', 2022, 3);"
		"INSERT INTO COURSE VALUES(50005, 'Pyschology', 'BCOS', 'Will Wundt', '8:00 AM', 'M W F', 'Fall', 2022, 3);"
		"INSERT INTO COURSE VALUES(50006, 'Chemistry', 'BSME', 'Alfred Nobel', '7:00 PM', 'M W F', 'Winter', 2022, 2);"
	);

	exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Data Fail" << std::endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Data Successfully Inserted" << std::endl;

	/***********************************************
	 print all data in the table with SELECT * FROM
	 create string with query then execute
	 **********************************************/
	string query = "SELECT * FROM COURSE;";

	cout << endl << query << endl;		//print the string to screen

	// you need the callback function this time since there could be multiple rows in the table
	sqlite3_exec(db, query.c_str(), callback, NULL, NULL);
	


	while (hasExit == false)
	{
		cout << "What is your first name?: ";
		cin >> user_first_name;
		cout << "What is your last name?: ";
		cin >> user_last_name;
		cout << "What is your ID?: ";
		cin >> user_ID;
		cout << "Are you a Student, Instructor, or Admin?: ";
		cin >> userType;
		cout << "Would you like to Exit the program?: ";
		cin >> exitchoice;
		std::transform(exitchoice.begin(), exitchoice.end(), exitchoice.begin(), ::tolower);
		if (exitchoice == "yes")
			hasExit = true;
		else
			hasExit = false;
		std::transform(userType.begin(), userType.end(), userType.begin(), ::tolower);
		if (hasExit == false)
		{
			if (userType == "student") {
				Student studentUser = Student(user_first_name, user_last_name, user_ID);
				while (hasExitUser == false) {
					cout << " 1 - Search Course \n 2 - Add Course \n 3 - Remove Course \n 4 - Print Schedule \n 0 - Exit \n";
					cin >> user_input;
					if (user_input == 1)
					{
						cout << "What is the name of the Course that you want to Search?: ";
						cin >> course_add_drop;
						//std::transform(course_add_drop.begin(), course_add_drop.end(), course_add_drop.begin(), ::toupper);
						cout << "What is the CRN of the Course that you want to Search?: ";
						cin >> Course_CRN;
						cout << "What Department does the course belong to?: ";
						cin >> department_course;
						std::cin.ignore();
						cout << "Who is the Instructor of the course searched?: ";
						std::getline(cin, course_instructor);
						//cin >> course_instructor;
						cout << "What Time does the class start (Enter: XX:XX AM/PM)?: ";
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
						studentUser.search_course(db, course_add_drop, Course_CRN, department_course, course_instructor, course_start_time, Meeting_times, course_semester, course_year, course_credits);
					}
					else if (user_input == 2)
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
						return_v = studentUser.add_course(course_add_drop, Course_CRN, department_course, course_instructor, course_start_time, Meeting_times, course_semester, course_year, course_credits);
						int rc = sqlite3_exec(db, return_v.c_str(), nullptr, nullptr, &errMsg);
						if (rc != SQLITE_OK) {
							std::cerr << "SQL error while adding course: " << errMsg << std::endl;
							sqlite3_free(errMsg);
						}
						else {
							std::cout << "Course successfully added into the database.\n";
						}
					}
					else if (user_input == 3)
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
						return_v = studentUser.remove_course(course_add_drop, Course_CRN, department_course, course_instructor, course_start_time, Meeting_times, course_semester, course_year, course_credits);
						int rc = sqlite3_exec(db, return_v.c_str(), nullptr, nullptr, &errMsg);
						if (rc != SQLITE_OK) {
							std::cerr << "SQL error while deleting course: " << errMsg << std::endl;
							sqlite3_free(errMsg);
						}
						else {
							std::cout << "Course successfully removed from the database.\n";
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
			else if (userType == "instructor") {
				Instructor instructorUser = Instructor(user_first_name, user_last_name, user_ID);
				while (hasExitUser == false) {
					cout << " 1 - Print Schedule \n 2 - Print Class List (Students ONLY) \n 3 - Search Course \n 0 - Exit \n";
					cin >> user_input;
					if (user_input == 1)
					{
						query = instructorUser.print_schedule();
						cout << endl << query << endl;		//print the string to screen

						// you need the callback function this time since there could be multiple rows in the table
						sqlite3_exec(db, query.c_str(), callback, NULL, NULL);
					}
					else if (user_input == 2)
					{
						instructorUser.print_class_list(student_query);
						char* errMsg = nullptr;
						int rc;
						cout << endl << student_query << endl;
						rc = sqlite3_exec(db, student_query.c_str(), callback, NULL, NULL);
						if (rc != SQLITE_OK) {
							std::cerr << "SQL error (Student): " << errMsg << std::endl;
							sqlite3_free(errMsg);
						}
					}
					else if (user_input == 3)
					{
						cout << "What is the name of the Course that you want to Search?: ";
						cin >> course_add_drop;
						//std::transform(course_add_drop.begin(), course_add_drop.end(), course_add_drop.begin(), ::toupper);
						cout << "What is the CRN of the Course that you want to Search?: ";
						cin >> Course_CRN;
						cout << "What Department does the course belong to?: ";
						cin >> department_course;
						std::cin.ignore();
						cout << "Who is the Instructor of the course searched?: ";
						std::getline(cin, course_instructor);
						//cin >> course_instructor;
						cout << "What Time does the class start (Enter: XX:XX AM/PM)?: ";
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
						instructorUser.search_course(db, course_add_drop, Course_CRN, department_course, course_instructor, course_start_time, Meeting_times, course_semester, course_year, course_credits);
					}
					else if (user_input == 0)
					{
						hasExitUser = true;
					}
				}

			}
			else if (userType == "admin") {
				Admin adminUser = Admin(user_first_name, user_last_name, user_ID);
				while (hasExitUser == false) {
					cout << " 1 - Add Course \n 2 - Remove Course \n 3 - Add User \n 4 - Remove User \n 5 - Search Roster \n 6 - Print Roster \n 7 - Search Course \n 8 - Print Course \n 0 - Exit \n";
					cin >> user_input;
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
						return_v = adminUser.add_course(course_add_drop, Course_CRN, department_course, course_instructor, course_start_time, Meeting_times, course_semester, course_year, course_credits);
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
						return_v = adminUser.remove_course(course_add_drop, Course_CRN, department_course, course_instructor, course_start_time, Meeting_times, course_semester, course_year, course_credits);
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
							cout << "User's Graduation Year?: ";
							cin >> user_add_Grad_year;
							cout << "User's Major?: ";
							cin >> user_add_Major;
						}
						else if (add_user_type == 2) {
							cout << "Instructor's Title?: ";
							cin >> user_add_Title;
							cout << "Instructor's Year of Hire?: ";
							cin >> user_add_YOH;
							cout << "Instructor's Department?: ";
							cin >> user_add_Department;
						}
						else if (add_user_type == 3) {
							cout << "Admin's Title?: ";
							cin >> user_add_Title;
							std::cin.ignore();
							cout << "Admin's Office?: ";
							std::getline(cin,user_add_Office);
						}
						return_v = adminUser.add_user(user_add_removef, user_add_removel, user_add_ID, user_add_Grad_year, user_add_Major, user_add_Email, add_user_type, user_add_Title, user_add_YOH, user_add_Department, user_add_Office);
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
						}
						else if (remove_user_type == 2) {
							cout << "Instructor's Title?: ";
							cin >> user_remove_Title;
							cout << "Instructor's Year of Hire?: ";
							cin >> user_remove_YOH;
							cout << "Instructor's Department?: ";
							cin >> user_remove_Department;
						}
						else if (remove_user_type == 3) {
							cout << "Admin's Title?: ";
							cin >> user_remove_Title;
							std::cin.ignore();
							cout << "Admin's Office?: ";
							std::getline(cin, user_remove_Office);
						}
						return_v = adminUser.remove_user(user_removef, user_removel, user_remove_ID, user_remove_Grad_year, user_remove_Major, user_remove_Email, remove_user_type, user_remove_Title, user_remove_YOH, user_remove_Department, user_remove_Office);
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
					else if (user_input == 5)
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
						adminUser.search_roster( db, user_searchf, user_searchl, user_search_ID, user_search_Grad_year, user_search_Major, user_search_Email, search_user_typestr, user_search_Title, user_search_YOH, user_search_Department, user_search_Office);
					}
					else if (user_input == 6)
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
					else if (user_input == 7)
					{
						cout << "What is the name of the Course that you want to Search?: ";
						cin >> course_add_drop;
						//std::transform(course_add_drop.begin(), course_add_drop.end(), course_add_drop.begin(), ::toupper);
						cout << "What is the CRN of the Course that you want to Search?: ";
						cin >> Course_CRN;
						cout << "What Department does the course belong to?: ";
						cin >> department_course;
						std::cin.ignore();
						cout << "Who is the Instructor of the course searched?: ";
						std::getline(cin, course_instructor);
						//cin >> course_instructor;
						cout << "What Time does the class start (Enter: XX:XX AM/PM)?: ";
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
						adminUser.search_courses(db, course_add_drop, Course_CRN, department_course, course_instructor, course_start_time, Meeting_times, course_semester, course_year, course_credits);
					}
					else if (user_input == 8)
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
			userType = "";
			user_first_name = "";
			user_last_name = "";
			user_ID = "";
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
			cout << "Would you like to Exit the program?: ";
			cin >> exitchoice;
			std::transform(exitchoice.begin(), exitchoice.end(), exitchoice.begin(), ::tolower);
			if (exitchoice == "yes")
				hasExit = true;
			else
				hasExit = false;
		}
	}
}
