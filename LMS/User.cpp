#include "User.h"
using namespace std;
// Function to validate whether a string has spaces or not
bool valid_Name_User(string name)
{
    for (int i = 0; i < name.length(); i++)
    {
        if (name.at(i) == ' ')
        {
            return true;
        }
    }
    return false;
}
// Constructor for User class with Library_Database pointer
User::User(Library_Database *libraryDB) : l_db(libraryDB)
{
    name = "";
    id = 0;
}
// Function to verify user's name and ID
bool User::verify(string n, int i)
{
    return n == name && i == id;
}
// Getter function for user's ID
int User::get_id() { return id; }
// Getter function for user's name
string User::get_name() { return name; }
// Setter function for user's ID
void User::set_id(int i) { id = i; }
// Setter function for user's name
void User::set_name(string n) { name = n; }
// Setter function for user's type
void User::set_type(string t) { type = t; }
// Getter function for user's type
string User::get_type() { return type; }
// Function to handle the user's panel
void User::user_panel(User *user)
{
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\t***** USER PORTAL *****\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n\n\n";
    while (1)
    {
        cout << "[1] CHECK RESERVED BOOKS\n";
        cout << "\n[2] CHECK LOST BOOKS\n";
        cout << "\n[3] CHECK BORROWED BOOKS\n";
        cout << "\n[4] CHECK ALL BOOKS\n";
        cout << "\n[5] SEARCH A BOOK\n";
        cout << "\n[6] BORROW A BOOK\n";
        cout << "\n[7] RETURN A BOOK\n";
        cout << "\n[8] REPORT A LOST BOOK\n";
        cout << "\n[9] CALCULATE FINE\n";
        cout << "\n[10] LOGOUT AS USER\n";
        cout << "\nENTER YOUR OPTION HERE: ";
        int choice;
        while (!(cin >> choice)) {
            cin.clear();  // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
            cout << "\nERROR! INVALID INPUT ENTERED, PLEASE ENTER AN INTEGER VALUE\n";
            cout << "\nPLEASE ENTER YOUR OPTION HERE AGAIN: ";
        }
        if (choice == 1)
        {
            cout << "\n=========================\n";
            cout << "| RESERVED BOOKS ARE: " << acc.get_n_reserved() << " |\n";
            cout << "=========================\n\n";
        }
        else if (choice == 2) {
            cout << "\n=====================\n";
            cout << "| LOST BOOKS ARE: " << acc.get_n_lost() << " |\n";
            cout << "=====================\n\n";
        }
        else if (choice == 3)
        {
            cout << endl;
            acc.display();
            cout << "\n=========================\n";
            cout << "| BORROWED BOOKS ARE: " << acc.get_n_borrowed() << " |\n";
            cout << "=========================\n\n";
        }
        else if (choice == 4) {
            cout << endl;
            l_db->displayuser();
        }
        else if (choice == 5)
            l_db->searchuser();
        else if (choice == 6)
        {
            cout << endl;
            l_db->displayuser();
            string type = user->get_type();
            if (acc.borrow(l_db->borrow_book(type))) {
                cout << "\n==============================\n";
                cout << "| BOOK BORROWED SUCCESSFULLY |\n";
                cout << "==============================\n\n";
            }
        }
        else if (choice == 7)
        {
            cout << endl;
            acc.display();
            cout << "ENTER ISBN OF BOOK YOU WANT TO RETURN [NO SPACE ALLOWED]: ";
            string isbn;
            getline(cin >> ws, isbn);
            while (valid_Name_User(isbn))
            {
                cout << "\nERROR! SPACES WERE DETECTED IN BOOK ISBN\n";
                cout << "\nPLEASE ENTER ISBN OF BOOK YOU WANT TO RETURN AGAIN [NO SPACE ALLOWED]: ";
                getline(cin >> ws, isbn);
            }
            if (acc.return_book(isbn))
            {
                cout << "\n==============================\n";
                cout << "| BOOK RETURNED SUCCESSFULLY |\n";
                cout << "==============================\n\n";
            }
        }
        else if (choice == 8) {
            if (acc.report_loss()) {
                cout << "\n==============================\n";
                cout << "| BOOK REPORTED SUCCESSFULLY |\n";
                cout << "==============================\n\n";
            }
        }
        else if (choice == 9) {
            acc.calculate_fine();
        }
        else if (choice == 10)
            return;
    }
}
