
#include <iostream>
#include <algorithm>
#include "User.h"
#include "Student.h"
#include "Instructor.h"
#include "Admin.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

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
					cout << " 1 - Search Course \n 2 - Add-Drop Course \n 3 - Print Schedule \n 0 - Exit \n";
					cin >> user_input;
					if (user_input == 1)
					{
						cout << "What course do you want to search?: ";
						cin >> course_searched;
						studentUser.search_course(course_searched);
					}
					else if (user_input == 2)
					{
						cout << "Do you want to add or drop a course?: ";
						cin >> course_add_drop;
						std::transform(course_add_drop.begin(), course_add_drop.end(), course_add_drop.begin(), ::tolower);
						cout << "What course do you want to " << course_add_drop << "?: ";
						cin >> course_searched;
						studentUser.add_drop_course(course_searched, course_add_drop);
					}
					else if (user_input == 3)
					{
						cout << "Do you want to Print Schedule?: ";
						cin >> print_schedule;
						std::transform(print_schedule.begin(), print_schedule.end(), print_schedule.begin(), ::tolower);
						studentUser.print_schedule();
						//cout << "What course do you want to print?: ";
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
					cout << " 1 - Print Schedule \n 2 - Print Class List \n 3 - Search Course \n 0 - Exit \n";
					cin >> user_input;
					if (user_input == 1)
					{
						cout << "Do you want to Print Schedule?: ";
						cin >> print_schedule;
						std::transform(print_schedule.begin(), print_schedule.end(), print_schedule.begin(), ::tolower);
						instructorUser.print_schedule();
						//cout << "What course do you want to print?: ";
					}
					else if (user_input == 2)
					{
						cout << "Which course do you want to print the class list for?: ";
						cin >> class_list_print;
						std::transform(class_list_print.begin(), class_list_print.end(), class_list_print.begin(), ::toupper);
						instructorUser.print_class_list(class_list_print);
					}
					else if (user_input == 3)
					{
						cout << "What course do you want to search?: ";
						cin >> course_searched;
						instructorUser.search_course(course_searched);
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
					cout << " 1 - Add Course \n 2 - Remove Course \n 3 - Add User \n 4 - Remove User \n 5 - Add Student \n 6 - Remove Student \n 7 - Search Roster \n 8 - Print Roster \n 9 - Search Course \n 10 - Print Course \n 0 - Exit \n";
					cin >> user_input;
					if (user_input == 1)
					{
						cout << "What Course do you want to add?: ";
						cin >> course_add_drop;
						std::transform(course_add_drop.begin(), course_add_drop.end(), course_add_drop.begin(), ::toupper);
						adminUser.add_course(course_add_drop);
					}
					else if (user_input == 2)
					{
						cout << "What Course do you want to remove?: ";
						cin >> course_add_drop;
						std::transform(course_add_drop.begin(), course_add_drop.end(), course_add_drop.begin(), ::toupper);
						adminUser.remove_course(course_add_drop);
					}
					else if (user_input == 3)
					{
						cout << "Which user do you want to add?: ";
						cin >> user_add_remove;
						adminUser.add_user(user_add_remove);
					}
					else if (user_input == 4)
					{
						cout << "Which user do you want to remove?: ";
						cin >> user_add_remove;
						adminUser.add_user(user_add_remove);
					}
					else if (user_input == 5)
					{
						cout << "Which student do you want to add?: ";
						cin >> user_add_remove;
						cout << "Which course do you want to add them to?: ";
						cin >> course_add_drop;
						adminUser.add_student_course(user_add_remove, course_add_drop);
					}
					else if (user_input == 6)
					{
						cout << "Which student do you want to remove?: ";
						cin >> user_add_remove;
						cout << "Which course do you want to remove them from?: ";
						cin >> course_add_drop;
						adminUser.remove_student_course(user_add_remove, course_add_drop);
					}
					else if (user_input == 7)
					{
						cout << "Which course do you want to search the roster for?: ";
						cin >> course_search_roster;
						adminUser.search_roster(course_search_roster);
					}
					else if (user_input == 8)
					{
						cout << "Which course do you want to print the roster for?: ";
						cin >> course_print_roster;
						adminUser.print_roster(course_print_roster);
					}
					else if (user_input == 9)
					{
						cout << "What course do you want to search?: ";
						cin >> course_searched;
						adminUser.search_courses(course_searched);
					}
					else if (user_input == 10)
					{
						cout << "What course do you want to print?: ";
						cin >> course_printed;
						adminUser.print_courses(course_printed);
					}
					else if (user_input == 0)
					{
						hasExitUser = true;
					}
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