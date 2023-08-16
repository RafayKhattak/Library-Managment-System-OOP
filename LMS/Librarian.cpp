#include "Librarian.h"
using namespace std;

// Default constructor
Librarian::Librarian() : name(""), id(0), password(""), library(NULL) {}

// Parameterized constructor
Librarian::Librarian(string nm, int id, string pwd, Library_Database* lib) : name(nm), id(id), password(pwd), library(lib) {}

// Setter for library database reference
void Librarian::set_libdb(Library_Database* lib) {
    library = lib;
}

// Setter for librarian's name
void Librarian::set_name(string nm) {
    name = nm;
}

// Setter for librarian's ID
void Librarian::set_id(int i) {
    id = i;
}

// Setter for librarian's password
void Librarian::set_password(string pwd) {
    password = pwd;
}

// Getter for librarian's name
string Librarian::get_name() {
    return name;
}

// Getter for librarian's password
string Librarian::get_password() {
    return password;
}

// Getter for librarian's ID
int Librarian::get_id() {
    return id;
}

// Verify librarian's credentials
bool Librarian::verify_librarian(int i, string pwd) {
    return i == id && pwd == password;
}

// Delay function for librarian portal
void libdelay() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

// Librarian portal function
void Librarian::librarian_portal() {
    bool loop = true;
    while (loop) {
        system("cls");
        int choice;
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t***** LIBRARIAN PORTAL *****\n";
        cout << "------------------------------------------------------------------------------------------------------------------------\n\n\n";
        cout << "[1] ADD A NEW BOOK\n";
        cout << endl;
        cout << "[2] SEARCH AN EXISTING BOOK\n";
        cout << endl;
        cout << "[3] DISPLAY ALL BOOKS\n";
        cout << endl;
        cout << "[4] DELETE AN EXISTING BOOK\n";
        cout << endl;
        cout << "[5] UPDATE AN EXISTING BOOK\n";
        cout << endl;
        cout << "[6] LOGOUT AS LIBRARIAN\n";
        cout << endl;
        cout << "ENTER YOUR CHOICE HERE: ";
        while (!(cin >> choice)) {
            cin.clear();  // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
            cout << "\n\nERROR! INVALID INPUT ENTERED, PLEASE ENTER AN INTEGER VALUE\n\n";
            cout << "ENTER YOUR CHOICE HERE: ";
        }
        if (choice == 1) {
            library->add();
        }
        else if (choice == 2) {
            library->search();
        }
        else if (choice == 3) {
            library->display();
        }
        else if (choice == 4) {
            library->Delete();
        }
        else if (choice == 5) {
            library->update();
        }
        else if (choice == 6) {
            loop = false;
        }
        else {
            cout << "\nERROR! INVALID OPTION ENTERED, PLEASE TRY AGAIN\n";
            std::thread t(libdelay);
            t.join();
        }
    }
}
