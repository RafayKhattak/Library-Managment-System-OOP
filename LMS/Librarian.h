#pragma once
#include <string>
#include <iostream>
#include "Library_Database.h"
#include "LMS.h" // Make sure to include this header if necessary

using namespace std;

class Librarian {
private:
    string name;
    int id;
    string password;
    Library_Database* library;

public:
    // Default constructor
    Librarian();

    // Parameterized constructor
    Librarian(string nm, int id, string pwd, Library_Database* lib);

    // Setter for librarian's name
    void set_name(string nm);

    // Setter for librarian's ID
    void set_id(int i);

    // Setter for librarian's password
    void set_password(string pwd);

    // Getter for librarian's name
    string get_name();

    // Getter for librarian's ID
    int get_id();

    // Getter for librarian's password
    string get_password();

    // Verify librarian's credentials
    bool verify_librarian(int i, string pwd);

    // Access librarian's portal
    void librarian_portal();

    // Setter for library database reference
    void set_libdb(Library_Database* lib);
};
