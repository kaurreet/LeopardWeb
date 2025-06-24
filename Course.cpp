#include "Course.h"
#include <iostream>
#include <string>
#include <vector>
#include "sqlite3.h" 
#include <stdio.h>
#include <string>
#include <set>
Course::Course(int in_crn, string in_title, string in_department, string in_instructor, string in_time, string in_days, string in_semester, int in_year, int in_credits) {
     crn = in_crn;
     title = in_title;
     department = in_department;
     instructor = in_instructor;
     time = in_time;
     days = in_days;
     semester = in_semester;
     year = in_year;
     credits = in_credits;
}
int Course::get_CRN(){
    return crn;
}
string Course::get_title(){
    return title;
}
string Course::get_department(){
    return department;
}
string Course::get_instructor() {
    return instructor;
}
string Course::get_time(){
    return time;
}
string Course::get_days(){
    return days;
}
string Course::get_semester(){
    return semester;
}
int Course::get_year(){
    return year;
}
int Course::get_credits(){
    return credits;
}
