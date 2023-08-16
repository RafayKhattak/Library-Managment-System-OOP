#pragma once
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm> // For std::transform
#include <cctype>    // For std::tolower
#include "Librarian.h" // Assuming Librarian.h is another user-defined header file
#include "Library_database.h" // Assuming Library_database.h is another user-defined header file
#include "User.h" // Assuming User.h is another user-defined header file
#include "Staff.h" // Assuming Staff.h is another user-defined header file

using namespace std;

// Forward declarations for class names
class Librarian;
class Library_Database;
class User;
class Staff;

class Library_Management_System {
private:
    int usertype; // User type (e.g., admin, librarian, user, etc.)
    string username; // Username of the currently logged-in user
    string password; // Password of the currently logged-in user
    bool logged_in; // Flag to indicate whether a user is currently logged in
    Librarian* librarians; // Pointer to an array of Librarian objects
    Library_Database* l_db; // Pointer to a Library_Database object
    int lib_index; // Index to keep track of the number of librarians
    User** users; // Pointer to an array of User pointers
    int user_index; // Index to keep track of the number of users

public:
    // Getter methods
    int get_user_type();
    string get_user_name();
    string get_password();

    // Setter methods
    void set_user_type(int ust);
    void set_user_name(string usn);
    void set_password(string usp);

    // Constructor
    Library_Management_System();

    // Authentication methods
    bool login();
    bool logout();

    // Admin operations
    void add_librarian();
    void verify_librarian();
    void admin_portal();

    // User registration and login
    bool register_user();
    bool login_user();
};
