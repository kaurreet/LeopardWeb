#include "Course.h"
#include <iostream>
#include <string>
#include <vector>
#include "sqlite3.h" 
#include <stdio.h>
#include <string>
#include <set>

Course::Course() {};
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
Course::Course(string in_title) {
    title = in_title;
}

void Course::set_CRN(int in_CRN) {
    crn = in_CRN;
}

void	Course::set_title(string in_title){
    title = in_title;
}
void	Course::set_department(string in_department){
    department = in_department;
}
void	Course::set_instructor(string in_instructor){
    instructor = in_instructor;
}
void	Course::set_starttime(string in_starttime){
    time = in_starttime;
}
void	Course::set_meetingtime(string in_meetingtime){
    days = in_meetingtime;
}
void	Course::set_semester(string in_semester){
    semester = in_semester;
}
void	Course::set_year(int in_year){
    year = in_year;
}
void	Course::set_credits(int in_credits){
    credits = in_credits;
}
void	Course::set_studentID(int in_ID){
    studentID = in_ID;
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

int Course::get_studentID() {
    return studentID;
}
