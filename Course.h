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
public:
    Course();
    Course(int in_crn, string in_title, string in_department, string in_instructor, string in_time, string in_days, string in_semester, int in_year, int in_credits);
    int get_CRN();
    string get_title();
    string get_department();
    string get_instructor();
    string get_time();
    string get_days();
    string get_semester();
    int get_year();
    int get_credits();

    
    void set_title(const string& in_title);
    void set_CRN(const int& in_crn);
    void set_department(const string& in_department);
    void set_instructor(const string& in_instructor);

};

