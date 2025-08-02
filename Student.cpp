#include <iostream>
#include <algorithm>
#include "Student.h"
#include <string>
#include <sstream>
#include <iomanip>
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
using std::setw;
//constructor
Student::Student() {}

Student::Student(string in_fname, string in_lname, int in_ID) {
	first_name = in_fname;
	last_name = in_lname;
	ID = in_ID;
}

Student::Student(string in_fname, string in_lname, int in_ID, string in_email, int in_gradyear, string in_major){
	first_name = in_fname;
	last_name = in_lname;
	ID = in_ID;
	email = in_email;
	gradYear = in_gradyear;
	major = in_major;
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

//bool Student::check_conflict(sqlite3* db, string course_title, int student_id) {
//	sqlite3_stmt* stmt;
//	string sql = "SELECT TIME, DoftW FROM REGISTERED WHERE StudentID = " + to_string(student_id) + ";";
//	string new_course_sql = "SELECT TIME, DoftW FROM COURSE WHERE TITLE = '" + course_title + "';";
//
//	string new_time, new_days;
//	if (sqlite3_prepare_v2(db, new_course_sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
//		if (sqlite3_step(stmt) == SQLITE_ROW) {
//			new_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
//			new_days = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
//		}
//		else {
//			sqlite3_finalize(stmt);
//			return false;
//		}
//		sqlite3_finalize(stmt);
//	}
//
//	if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
//		while (sqlite3_step(stmt) == SQLITE_ROW) {
//			string existing_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
//			string existing_days = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
//			if (new_time == existing_time && new_days == existing_days) {
//				sqlite3_finalize(stmt);
//				return true;
//			}
//		}
//		sqlite3_finalize(stmt);
//	}
//	return false;
//}

bool Student::check_conflict(sqlite3* db, string course_title, int student_id) {
    if (!db) {
        std::cerr << "Error: Database pointer is null.\n";
        return false;
    }

    sqlite3_stmt* stmt = nullptr;
    bool has_conflict = false;

    // Get the course details to check
    string course_query = "SELECT TIME, DoftW, SEMESTER, YEAR FROM COURSE WHERE TITLE = ?;";
    int rc = sqlite3_prepare_v2(db, course_query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK || !stmt) {
        std::cerr << "Error preparing course query: " << sqlite3_errmsg(db) << endl;
        if (stmt) sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_bind_text(stmt, 1, course_title.c_str(), -1, SQLITE_STATIC);
    string new_time, new_days, new_semester;
    int new_year = 0;
    bool course_found = false;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        course_found = true;
        const char* time_text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        const char* days_text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* semester_text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        new_time = time_text ? time_text : "N/A";
        new_days = days_text ? days_text : "N/A";
        new_semester = semester_text ? semester_text : "N/A";
        new_year = sqlite3_column_int(stmt, 3);
    } else {
        std::cout << "Course '" << course_title << "' not found in the database.\n";
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    stmt = nullptr;

    auto clean_days = [](string& days) -> bool {
        if (days.empty()) {
            days = "N/A";
            return false;
        }
        // Remove leading/trailing spaces and extra spaces between days
        days.erase(std::remove_if(days.begin(), days.end(), [](char c) { return c == ' '; }), days.end());
        for (char c : days) {
            if (c != 'M' && c != 'W' && c != 'F' && c != 'T' && c != 'H') {
                days = "N/A";
                return false;
            }
        }
        return true;
    };

    if (!clean_days(new_days)) {
        std::cerr << "Warning: Invalid days format for course '" << course_title << "': " << new_days << ". Using 'N/A'.\n";
    }
    string enrolled_query = "SELECT TITLE, TIME, DoftW, SEMESTER, YEAR FROM REGISTERED WHERE StudentID = ?;";
    rc = sqlite3_prepare_v2(db, enrolled_query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK || !stmt) {
        std::cerr << "Error preparing enrolled courses query: " << sqlite3_errmsg(db) << endl;
        if (stmt) sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_bind_text(stmt, 1, std::to_string(student_id).c_str(), -1, SQLITE_STATIC);

    // Print header for conflict check results
    std::cout << "\nChecking conflicts for course: " << course_title << " (" << new_time << ", " << new_days << ", " << new_semester << " " << new_year << ")\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << std::left << std::setw(30) << "Enrolled Course" << std::setw(12) << "Time" << std::setw(12) << "Days" << std::setw(12) << "Semester" << std::setw(6) << "Year" << std::setw(8) << "Conflict" << "\n";
    std::cout << std::string(80, '-') << "\n";

    auto parse_time = [](const string& time_str) -> int {
        if (time_str.empty() || time_str == "N/A") {
            std::cerr << "Error: Empty or invalid time string: " << time_str << "\n";
            return 0;
        }
        int hours = 0, minutes = 0;
        char period[3] = {0};
        if (sscanf_s(time_str.c_str(), "%d:%d %2s", &hours, &minutes, period, (unsigned)sizeof(period)) != 3) {
            std::cerr << "Error: Invalid time format: " << time_str << "\n";
            return 0;
        }
        if (hours < 1 || hours > 12 || minutes < 0 || minutes > 59) {
            std::cerr << "Error: Invalid time values: " << time_str << "\n";
            return 0;
        }
        std::string period_str = period;
        if (period_str != "AM" && period_str != "PM") {
            std::cerr << "Error: Invalid period (must be AM or PM): " << time_str << "\n";
            return 0;
        }
        if (period_str == "PM" && hours != 12) hours += 12;
        if (period_str == "AM" && hours == 12) hours = 0;
        return hours * 60 + minutes;
    };

    int new_time_minutes = parse_time(new_time);
    int new_end_time_minutes = new_time_minutes ? new_time_minutes + 50 : 0; // Assume 50-minute classes

    if (new_time_minutes == 0) {
        std::cerr << "Error: Failed to parse time for course '" << course_title << "'. No conflict check performed.\n";
        sqlite3_finalize(stmt);
        return false;
    }

    // Check for conflicts
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* title_text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        const char* time_text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* days_text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        const char* semester_text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        string enrolled_title = title_text ? title_text : "N/A";
        string enrolled_time = time_text ? time_text : "N/A";
        string enrolled_days = days_text ? days_text : "N/A";
        string enrolled_semester = semester_text ? semester_text : "N/A";
        int enrolled_year = sqlite3_column_int(stmt, 4);

        if (!clean_days(enrolled_days)) {
            std::cerr << "Warning: Invalid days format for enrolled course '" << enrolled_title << "': " << enrolled_days << ". Using 'N/A'.\n";
        }
        if (new_semester == enrolled_semester && new_year == enrolled_year) {           // Check if semester and year match
            bool days_overlap = false;
            if (new_days != "N/A" && enrolled_days != "N/A" && new_days == enrolled_days) { // Check if days overlap (e.g., "M W F" and "M W" share M and W)
                days_overlap = true;
            } else if (new_days != "N/A" && enrolled_days != "N/A") {
                for (char day : {'M', 'W', 'F', 'T', 'H'}) {
                    if (new_days.find(day) != string::npos && enrolled_days.find(day) != string::npos) {
                        days_overlap = true;
                        break;
                    }
                }
            }
            if (days_overlap) {
                int enrolled_time_minutes = parse_time(enrolled_time);
                int enrolled_end_time_minutes = enrolled_time_minutes ? enrolled_time_minutes + 50 : 0;

                if (enrolled_time_minutes != 0 && new_time_minutes != 0 &&
                    ((new_time_minutes >= enrolled_time_minutes && new_time_minutes < enrolled_end_time_minutes) ||
                     (enrolled_time_minutes >= new_time_minutes && enrolled_time_minutes < new_end_time_minutes))) { // Check time overlap
                    has_conflict = true;
                    std::cout << std::left << std::setw(25) << enrolled_title << std::setw(12) << enrolled_time
                              << std::setw(12) << enrolled_days << std::setw(12) << enrolled_semester
                              << std::setw(6) << enrolled_year << std::setw(8) << "Yes" << "\n";
                } else {
                    std::cout << std::left << std::setw(25) << enrolled_title << std::setw(12) << enrolled_time
                              << std::setw(12) << enrolled_days << std::setw(12) << enrolled_semester
                              << std::setw(6) << enrolled_year << std::setw(8) << "No" << "\n";
                }
            } else {
                std::cout << std::left << std::setw(25) << enrolled_title << std::setw(12) << enrolled_time
                          << std::setw(12) << enrolled_days << std::setw(12) << enrolled_semester
                          << std::setw(6) << enrolled_year << std::setw(8) << "No" << "\n";
            }
        } else {
            std::cout << std::left << std::setw(25) << enrolled_title << std::setw(12) << enrolled_time
                      << std::setw(12) << enrolled_days << std::setw(12) << enrolled_semester
                      << std::setw(6) << enrolled_year << std::setw(8) << "No" << "\n";
        }
    }
    sqlite3_finalize(stmt);

    if (!course_found) {
        return false;
    }
    return has_conflict;
}

//destructor
Student::~Student() {

}
