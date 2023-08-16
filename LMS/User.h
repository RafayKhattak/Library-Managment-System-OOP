#pragma once
#include <string>
#include <iostream>
#include "Account.h" // Include the Account class header
#include "Library_database.h" // Include the Library_Database class header
using namespace std;

class User {
protected:
    Library_Database* l_db; // Pointer to the Library Database
private:
    Account acc; // User's account information
    string name; // User's name
    int id; // User's ID
    string type; // User's type (e.g., student, staff)
public:
    // Default constructor
    User();

    // Constructor with Library Database pointer
    User(Library_Database* libraryDB);

    // Function to verify user information
    bool verify(string n, int i);

    // Getter function for user's ID
    int get_id();

    // Getter function for user's name
    string get_name();

    // Setter function for user's ID
    void set_id(int i);

    // Setter function for user's name
    void set_name(string n);

    // Setter function for user's type
    void set_type(string t);

    // Function to display the user's panel
    void user_panel(User* user);

    // Getter function for user's type
    string get_type();
};
