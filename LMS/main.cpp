//Importing header files
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <cctype>
#include <string>
#include <limits>
#include "LMS.h" // LMS.h is a user-defined header file

using namespace std;

// Function to introduce a delay of 5 seconds
void ENTRYDELAY() {
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

// Function to introduce a delay of 3 seconds (Admin related delay)
void AdminDelay() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

// Function to introduce a delay of 2 seconds (Smaller delay)
void smoldelay() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

// Function to check if a string contains spaces (for admin name validation)
bool valid_name(string admin_name) {
    for (int i = 0; i < admin_name.length(); i++) {
        if (admin_name.at(i) == ' ') {
            return true;
        }
    }
    return false;
}

// Function to check if a string contains spaces (for admin password validation)
bool valid_password(string admin_password) {
    for (int i = 0; i < admin_password.length(); i++) {
        if (admin_password.at(i) == ' ') {
            return true;
        }
    }
    return false;
}

int main() {
    Library_Management_System lms; // Assuming Library_Management_System class is defined in LMS.h
    char option;
    string admin_name = "";
    string admin_password = "";

    // Printing welcome message
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t*****\t WELCOME TO THE OFFICIAL FAST NUCES LIBRARY MANAGEMENT SYSTEM CREATED BY RAFAY KHATTAK\t *****\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\n";
    cout << "\n";

    // Prompting user to proceed further
    cout << "[NOTE]: TO PROCEED FURTHER, REGISTER AN ADMIN ACCOUNT FOR THIS SYSTEM\n\n";
    cout << "DO YOU WISH TO PROCEED? [Y/N]: ";
    cin >> option;

    // Validating the input
    while (option != 'n' && option != 'N' && option != 'Y' && option != 'y') {
        cout << "ERROR! INVALID INPUT ENTERED, PLEASE TRY AGAIN.\n";
        cout << "DO YOU WISH TO PROCEED? [Y/N]: ";
        cin >> option;
    }

    if (option == 'Y' || option == 'y') {
        system("cls");

        // Admin registration process
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\t\t\t\t\t***** ADMIN REGISTRATION PORTAL *****\n";
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\n";
        cout << "\n";
        cout << "ENTER ADMIN USERNAME [NO SPACES ALLOWED]: ";

        // Reading admin name (including whitespace)
        getline(cin >> ws, admin_name);

        // Validating admin name for spaces
        while (valid_name(admin_name)) {
            cout << "\nERROR! SPACES WERE DETECTED IN ADMIN USERNAME\n";
            cout << "\nPLEASE ENTER ADMIN USERNAME AGAIN [NO SPACES ALLOWED]: ";
            getline(cin >> ws, admin_name);
        }

        cout << "\nENTER ADMIN PASSWORD [NO SPACES ALLOWED]: ";

        // Reading admin password (including whitespace)
        getline(cin >> ws, admin_password);

        // Validating admin password for spaces
        while (valid_password(admin_password)) {
            cout << "\nERROR! SPACES WERE DETECTED IN ADMIN PASSWORD\n";
            cout << "\nPLEASE ENTER ADMIN PASSWORD AGAIN [NO SPACES ALLOWED]: ";
            getline(cin >> ws, admin_password);
        }

        cout << "\n*** CONGRATS! ADMIN CREATED SUCCESSFULLY ***\n";

        // Introducing a small delay
        std::thread t(smoldelay);
        t.join();
    }

    // If the user chooses not to proceed
    if (option == 'N' || option == 'n') {
        system("cls");
        cout << "\t\t***** ADMIN WAS NOT CREATED, SYSTEM WILL SHUTDOWN IN 5 SECONDS. HAVE A GOOD DAY! *****";

        // Introducing a delay before shutting down
        std::thread t(ENTRYDELAY);
        t.join();
        return 0;
    }

    // Setting admin name and password in the Library_Management_System instance
    lms.set_user_name(admin_name);
    lms.set_password(admin_password);

    while (1) {
        system("cls");
        int choice;

        // Main menu
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\t\t\t\t\t***** LIBRARY MANAGEMENT SYSTEM PORTAL *****\n";
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\n";
        cout << "[1] SIGN IN AS AN ADMINISTRATOR\n";
        cout << "\n";
        cout << "[2] SIGN IN AS A LIBRARIAN\n";
        cout << "\n";
        cout << "[3] REGISTER AS A NEW USER\n";
        cout << "\n";
        cout << "[4] SIGN IN AS A USER\n";
        cout << "\n";
        cout << "ENTER YOUR CHOICE HERE: ";

        // Validating the choice input
        while (!(cin >> choice)) {
            cin.clear();  // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
            cout << "ERROR! INVALID INPUT ENTERED, PLEASE ENTER AN INTEGER VALUE\n";
            cout << "ENTER YOUR CHOICE HERE: ";
        }

        // Handling user's choice
        if (choice == 1) {
            system("cls");

            // Admin login process
            cout << "------------------------------------------------------------------------------------------------------------------------\n";
            cout << "\t\t\t\t\t***** LIBRARY MANAGEMENT SYSTEM PORTAL *****\n";
            cout << "------------------------------------------------------------------------------------------------------------------------\n\n\n";

            if (lms.login()) {
                cout << "\n***** LOGIN SUCCESSFUL, YOU WILL NOW BE REDIRECTED TO ADMIN PORTAL IN A FEW SECONDS *****\n\n";

                // Introducing a delay before redirection
                std::thread t(AdminDelay);
                t.join();

                // Proceed to admin portal
                lms.admin_portal();
            }
            else {
                cout << "\n*** WRONG CREDENTIALS ENTERED, YOU WILL BE REDIRECTED TO LMS PORTAL ***\n";

                // Introducing a delay before redirection
                std::thread t(AdminDelay);
                t.join();
            }
        }
        else if (choice == 2) {
            lms.verify_librarian(); // verify_librarian is a method in the Library_Management_System class
        }
        else if (choice == 3) {
            lms.register_user(); // register_user is a method in the Library_Management_System class
        }
        else if (choice == 4) {
            lms.login_user(); // login_user is a method in the Library_Management_System class
        }
        else {
            cout << "ERROR! INVALID OPTION ENTERED, PLEASE TRY AGAIN\n";

            // Introducing a delay before re-displaying the main menu
            std::thread t(AdminDelay);
            t.join();
        }
    }

    return 0;
}
