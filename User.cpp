#include "User.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
//constructor
User::User() {

}
User::User(string in_fname, string in_lname, int in_ID) {
	first_name = in_fname;
	last_name = in_lname;
	ID = in_ID;
}
//methods
string User::get_first_name() {
	//first_name = in_first_name;
	return first_name;
	
}
string User::get_last_name() {
	return last_name;
	
}
int User::get_ID() {
	return ID;
	
}
void User::print_all() {
	cout << first_name << endl;
	cout << last_name << endl;
	cout << ID << endl;
	//return first_name, last_name, ID;
	
}
User::~User() {

}
