#include "Staff.h" // Include the Staff class header
using namespace std;

// Constructor implementation for Staff class
Staff::Staff(string n, int i, string de, string des, Library_Database* libraryDB, string t) : User(libraryDB), dept(de), designation(des) {
    set_name(n); // Set the name using the provided argument
    set_id(i); // Set the ID using the provided argument
    set_type(t); // Set the type using the provided argument
}

// Implementation of the getter function for department
string Staff::get_dept() {
    return dept;
}

// Implementation of the getter function for designation
string Staff::get_designation() {
    return designation;
}

// Implementation of the setter function for department
void Staff::set_dept(string d) {
    dept = d;
}

// Implementation of the setter function for designation
void Staff::set_designation(string d) {
    designation = d;
}
