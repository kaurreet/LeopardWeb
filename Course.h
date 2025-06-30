#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "sqlite3.h" 
#include <stdio.h>
#include <string>
#include <set>
using std::string;

class Course
{
    int crn;
    string title;
    string department;
    string instructor;
    string time;
    string days;
    string semester;
    int year;
    int credits;
    int studentID;
public:
    Course();
    Course(int in_crn, string in_title, string in_department, string in_instructor, string in_time, string in_days, string in_semester, int in_year, int in_credits);
    Course(string in_title);
    int get_CRN();

    void set_CRN(int in_CRN);
    void set_title(string in_title);
    void set_department(string in_department);
    void set_instructor(string in_instructor);
    void set_starttime(string in_starttime);
    void set_meetingtime(string in_meetingtime);
    void set_semester(string in_semester);
    void set_year(int in_year);
    void set_credits(int in_credits);
    void set_studentID(int in_ID);

    string get_title();
    string get_department();
    string get_instructor();
    string get_time();
    string get_days();
    string get_semester();
    int get_year();
    int get_credits();
    int get_studentID();
};

