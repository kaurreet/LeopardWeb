#include "User.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
//constructor
User::User() {
	first_name = "Andy";
	last_name = "Le";
}
User::User(string in_fname, string in_lname, string in_ID) {
	first_name = in_fname;
	last_name = in_lname;
	ID = in_ID;
}
//methods
void User::show_first_name() {
	cout << first_name;
	//return first_name;
	
}
void User::show_last_name() {
	cout << last_name;
	//return last_name;
	
}
void User::show_ID() {
	cout << ID;
	//return ID;
	
}
void User::show_all() {
	cout << first_name << endl;
	cout << last_name << endl;
	cout << ID << endl;
	//return first_name, last_name, ID;
	
}
User::~User() {

}