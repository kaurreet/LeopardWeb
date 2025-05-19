The assignments in this course are based on a single system – you will build, test, document, create a database for,
code, etc. the system in phases, one assignment at a time until you integrate the system later in the end of the semester. 
As a reminder, the following is a general description of the system; the requirements for Assignment 2 are after the 
system overview.
System Overview You will be designing a scheduling system for a university similar to LeopardWeb. The system will 
allow students, faculty, and an admin (such as the registrar) to add courses, search for courses, print schedules, etc. 
Here is a list of the requirements for scheduling system.
• Database of users: the system should work for 100 students, 10 instructors, and 1 admin, however, we will 
test with fewer.
• Database of courses: this will contain information such as the CRN, course name, times, and instructor.
• Three types of users:
o student – can register, can see available courses and their own schedule. 
o instructor – can see available courses and their own course roster.
o admin – can see everything, can edit courses/users/schedules.
• The system should include multiple semesters, print-out of schedule, scheduling preferences.
• The system as a whole and all components must be tested thoroughly.
The base class of the system is user with:
• Attributes: first name, last name, ID.
• Methods: set function for each attribute, and a function to print all info for the object.
There will be three derived classes:
• All derived classes must contain any additional attributes and appropriate set/get functions.
• student – the student class will have functions that allow them to search courses, add/drop courses, print 
their schedule.
• instructor – the instructor class will have functions that allow them to print their schedule, print their class 
list, and search for courses.
• admin – the admin class will have functions that allow them to add courses to the system, remove courses 
from the system, add/remove users, add/remove student from a course, search and print rosters and courses.
