#pragma once
#include "User.h" // Include the User class header
#include <string>
using namespace std;

// Staff class, inheriting from the User class
class Staff : public User {
private:
    string dept; // Department of the staff member
    string designation; // Designation of the staff member

public:
    // Constructor for Staff class
    Staff(string n, int i, string de, string des, Library_Database* libraryDB, string t);

    // Getter functions for department and designation
    string get_dept();
    string get_designation();

    // Setter functions for department and designation
    void set_dept(string d);
    void set_designation(string d);
};
