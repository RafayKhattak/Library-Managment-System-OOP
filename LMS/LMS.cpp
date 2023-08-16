#include "LMS.h"  // Including the user-defined header file
using namespace std;
// Function to validate a name (checks for spaces)
bool valid_Name(string name)
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
// Function to validate a password (checks for spaces)
bool valid_Password(string password)
{
    for (int i = 0; i < password.length(); i++)
    {
        if (password.at(i) == ' ')
        {
            return true;
        }
    }
    return false;
}
// Function to validate an ID (checks for ID = 0)
bool valid_Id(int id)
{
    if (id == 0)
    {
        return true;
    }
    return false;
}
// Delays for admin interface
void adminDelay()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
// Delays for librarian interface
void librariandelay()
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
}
// Converts a string to lowercase
string toLowerCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return std::tolower(c);
        });
    return result;
}
// Constructor for Library_Management_System class
Library_Management_System::Library_Management_System() : users(new User *[100]), user_index(0)
{
    l_db = new Library_Database;
    usertype = 1;
    username = "";
    password = "";
    logged_in = false;
    librarians = new Librarian[20];
    lib_index = 0;
}
// Getter methods
int Library_Management_System::get_user_type()
{
    return usertype;
}
string Library_Management_System::get_user_name()
{
    return username;
}
string Library_Management_System::get_password()
{
    return password;
}
// Setter methods
void Library_Management_System::set_user_type(int ust)
{
    usertype = ust;
}
void Library_Management_System::set_user_name(string usn)
{
    username = usn;
}
void Library_Management_System::set_password(string usp)
{
    password = usp;
}
// Login function for admin
bool Library_Management_System::login()
{
    string usrnm, pswd;
    cout << "ENTER ADMIN USERNAME [NO SPACE ALLOWED]: ";
    cin >> usrnm;
    cout << "\nENTER ADMIN PASSWORD [NO SPACE ALLOWED]: ";
    cin >> pswd;
    if (usrnm == username && pswd == password)
    {
        logged_in = true;
    }
    return usrnm == username && pswd == password;
}
// Logout function for admin
bool Library_Management_System::logout()
{
    logged_in = false;
    return true;
}
// Function to add a librarian
void Library_Management_System::add_librarian()
{
    string nm, pwd;
    int id;
    system("cls");
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\t***** ADMIN PORTAL *****\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n\n";
    cout << "ENTER NEW LIBRARIAN NAME [NO SPACES ALLOWED]: ";
    getline(cin >> ws, nm);
    while (valid_Name(nm))
    {
        cout << "\nERROR! SPACES WERE DETECTED IN LIBRARIAN USERNAME\n";
        cout << "\nPLEASE ENTER LIBRARIAN USERNAME AGAIN [NO SPACES ALLOWED]: ";
        getline(cin >> ws, nm);
    }
    cout << "\nENTER LIBRARIAN ID NUMBER[ID = 0 NOT ALLOWED]: ";
    while (!(cin >> id)) {
        cin.clear();  // Clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
        cout << "\nERROR! INVALID INPUT ENTERED, PLEASE ENTER AN INTEGER VALUE\n";
        cout << "\nPLEASE ENTER NEW LIBRARIAN ID NUMBER AGAIN [ID = 0 NOT ALLOWED]: ";
    }

    while (valid_Id(id))
    {
        cout << "\nERROR! 0 WAS DETECTED IN LIBRARIAN ID\n";
        cout << "\nPLEASE ENTER NEW LIBRARIAN ID NUMBER AGAIN [ID = 0 NOT ALLOWED]: ";
        cin >> id;
    }
    cout << "\nENTER NEW LIBRARIAN PASSWORD [NO SPACES ALLOWED]: ";
    getline(cin >> ws, pwd);
    while (valid_Password(pwd))
    {
        cout << "\nERROR! SPACES WERE DETECTED IN LIBRARIAN PASSWORD\n";
        cout << "\nPLEASE ENTER LIBRARIAN PASSWORD AGAIN [NO SPACES ALLOWED]: ";
        getline(cin >> ws, pwd);
    }
    bool exists = false;
    for (int i = 0; i < lib_index; i++)
    {
        if (librarians[i].get_id() == id)
        {
            cout << "\n*** ERROR! A LIBRARIAN WITH SIMILAR ID ALREADY EXISTS. PLEASE TRY AGAIN! ***\n";
            exists = true;
        }
    }

    if (!exists)
    {
        librarians[lib_index].set_name(nm);
        librarians[lib_index].set_id(id);
        librarians[lib_index].set_password(pwd);
        librarians[lib_index++].set_libdb(l_db);
        cout << "\n*** A NEW LIBRARIAN HAS BEEN CREATED SUCCESSFULLY! ***";
    }
    
    std::thread t(adminDelay);
    t.join();
}
// Function to verify a librarian's credentials
void Library_Management_System::verify_librarian()
{
    string pwd;
    int id;
    system("cls");
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t***** LIBRARY MANAGMENT SYSTEM PORTAL *****\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n\n\n";
    cout << "ENTER LIBRARIAN ID [ID = 0 NOT ALLOWED]: ";
    while (!(cin >> id)) {
        cin.clear();  // Clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
        cout << "\nERROR! INVALID INPUT ENTERED, PLEASE ENTER AN INTEGER VALUE\n\n";
        cout << "PLEASE ENTER LIBRARIAN ID NUMBER AGAIN [ID = 0 NOT ALLOWED]: ";
    }
    while (valid_Id(id))
    {
        cout << "\nERROR! 0 WAS DETECTED IN LIBRARIAN ID\n\n";
        cout << "\nPLEASE ENTER LIBRARIAN ID NUMBER AGAIN [ID = 0 NOT ALLOWED]: ";
        cin >> id;
    }
    cout << "\nENTER LIBRARIAN PASSWORD [NO SPACES ALLOWED]: ";
    getline(cin >> ws, pwd);
    while (valid_Password(pwd))
    {
        cout << "\nERROR! SPACES WERE DETECTED IN LIBRARIAN PASSWORD\n\n";
        cout << "\nPLEASE ENTER LIBRARIAN PASSWORD AGAIN [NO SPACES ALLOWED]: ";
        getline(cin >> ws, pwd);
    }
    bool exists = false;
    for (int i = 0; i < lib_index; i++)
    {
        if (librarians[i].verify_librarian(id, pwd))
        {
            exists = true;
            cout << "\n\n***** LOGIN SUCCESSFULL, YOU WILL NOW BE REDIRECTED TO LIBRARIAN PORTAL IN A FEW SECONDS *****\n";
            std::thread t(librariandelay);
            t.join();
            system("cls");
            librarians[i].librarian_portal();
        }
    }

    if (!exists)
    {
        cout << "Librarean with such credentials doesn't exists" << endl;
    }
}
// Function for the admin portal
void Library_Management_System::admin_portal()
{
    while (1)
    {
        system("cls");
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t***** ADMIN PORTAL *****\n";
        cout << "------------------------------------------------------------------------------------------------------------------------\n\n";
        cout << "[1] ADD A NEW LIBRARIAN\n";
        cout << "\n";
        cout << "[2] LOGOUT AS ADMIN\n";
        cout << "\n";
        cout << "ENTER YOUR CHOICE HERE: ";
        int choice;
        while (!(cin >> choice)) {
            cin.clear();  // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
            cout << "ERROR! INVALID INPUT ENTERED, PLEASE ENTER AN INTEGER VALUE\n\n";
            cout << "ENTER YOUR CHOICE HERE: ";
        }
        if (choice == 1)
            add_librarian();
        else if (choice == 2)
            return;
        else
            cout << "ERROR! INVALID OPTION ENTERED, PLEASE TRY AGAIN\n";
            std::thread t(adminDelay);
            t.join();
    }
}
// Function to register a user
bool Library_Management_System::register_user()
{
    string name, d, desig;
    string type;
    int id;
    bool exists = false;
    system("cls");
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t***** LIBRARY MANAGMENT SYSTEM PORTAL *****\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n\n\n";
    cout << "ENTER NEW USER TYPE (STAFF | STUDENT) [NO SPACE ALLOWED]: ";
    getline(cin >> ws, type);
    while (valid_Name(type))
    {
        cout << "\nERROR! SPACES WERE DETECTED IN NEW USER TYPE\n";
        cout << "\nPLEASE ENTER NEW USER TYPE (STAFF | STUDENT) AGAIN [NO SPACE ALLOWED]: ";
        getline(cin >> ws, type);
    }
    type = toLowerCase(type);
    if (type != "staff" && type != "student")
    {
        cout << "\n*** ERROR! INVALID TYPE ENTERED ***" << endl;
        std::thread t(adminDelay);
        t.join();
        return false;
    }
    else if (type == "staff")
    {
        system("cls");
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\t\t\t\t\t***** LIBRARY MANAGMENT SYSTEM PORTAL *****\n";
        cout << "------------------------------------------------------------------------------------------------------------------------\n\n\n";
        cout << "ENTER NEW STAFF USERNAME [NO SPACE ALLOWED]: ";
        getline(cin >> ws, name);
        while (valid_Name(name))
        {
            cout << "\nERROR! SPACES WERE DETECTED IN NEW STAFF USERNAME\n";
            cout << "\nPLEASE ENTER NEW STAFF USERNAME AGAIN [NO SPACE ALLOWED]: ";
            getline(cin >> ws, name);
        }
        cout << "\nENTER NEW STAFF ID [ID = 0 NOT ALLOWED]: ";
        while (!(cin >> id)) {
            cin.clear();  // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
            cout << "\nERROR! INVALID INPUT ENTERED, PLEASE ENTER AN INTEGER VALUE\n";
            cout << "\nPLEASE ENTER NEW STAFF ID NUMBER AGAIN [ID = 0 NOT ALLOWED]: ";
        }

        while (valid_Id(id))
        {
            cout << "\nERROR! 0 WAS DETECTED IN STAFF ID\n";
            cout << "\nPLEASE ENTER NEW STAFF ID NUMBER AGAIN [ID = 0 NOT ALLOWED]: ";
            cin >> id;
        }
        cout << "\nENTER NEW STAFF DEPARTMENT [NO SPACE ALLOWED]: ";
        getline(cin >> ws, d);
        while (valid_Name(d))
        {
            cout << "\nERROR! SPACES WERE DETECTED IN NEW STAFF DEPARTMENT\n";
            cout << "\nPLEASE ENTER NEW STAFF DEPARTMENT AGAIN [NO SPACE ALLOWED]: ";
            getline(cin >> ws, d);
        }
        cout << "\nENTER NEW STAFF DESIGNATION [NO SPACE ALLOWED]: ";
        getline(cin >> ws, desig);
        while (valid_Name(desig))
        {
            cout << "\nERROR! SPACES WERE DETECTED IN NEW STAFF DESIGNATION\n";
            cout << "\nPLEASE ENTER NEW STAFF DESIGNATION AGAIN [NO SPACE ALLOWED]: ";
            getline(cin >> ws, desig);
        }

        for (int i = 0; i < user_index; i++)
        {
            if (id == users[i]->get_id())
            {
                cout << "\n*** ERROR! STAFF MEMBER ALREADY EXIST WITH SIMILAR ID ***\n\n" << endl;
                exists = true;
            }
        }
        if (!exists)
        {
            users[user_index++] = new Staff(name, id, d, desig, l_db,type);
            cout << "\n*** NEW STAFF MEMBER CREATED SUCCESSFULLY ***\n";
        }
        std::thread t(adminDelay);
        t.join();
    }
    else
    {
        system("cls");
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\t\t\t\t\t***** LIBRARY MANAGMENT SYSTEM PORTAL *****\n";
        cout << "------------------------------------------------------------------------------------------------------------------------\n\n\n";
        cout << "ENTER NEW STUDENT USERNAME [NO SPACE ALLOWED]: ";
        getline(cin >> ws, name);
        while (valid_Name(name))
        {
            cout << "\nERROR! SPACES WERE DETECTED IN NEW STUDENT USERNAME\n";
            cout << "\nPLEASE ENTER NEW STUDENT USERNAME AGAIN [NO SPACE ALLOWED]: ";
            getline(cin >> ws, name);
        }
        cout << "\nENTER NEW STUDENT ID [ID = 0 NOT ALLOWED]: ";
        while (!(cin >> id)) {
            cin.clear();  // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
            cout << "\nERROR! INVALID INPUT ENTERED, PLEASE ENTER AN INTEGER VALUE\n";
            cout << "\nPLEASE ENTER NEW STUDENT ID NUMBER AGAIN [ID = 0 NOT ALLOWED]: ";
        }

        while (valid_Id(id))
        {
            cout << "\nERROR! 0 WAS DETECTED IN STUDENT ID\n";
            cout << "\nPLEASE ENTER NEW STUDENT ID NUMBER AGAIN [ID = 0 NOT ALLOWED]: ";
            cin >> id;
        }
        cout << "\nENTER NEW STUDENT BATCH [NO SPACE ALLOWED]: ";
        getline(cin >> ws, d);
        while (valid_Name(d))
        {
            cout << "\nERROR! SPACES WERE DETECTED IN NEW STUDENT BATCH\n";
            cout << "\nPLEASE ENTER NEW STUDENT BATCH AGAIN [NO SPACE ALLOWED]: ";
            getline(cin >> ws, d);
        }
        cout << "\nENTER NEW STUDENT DESIGNATION [NO SPACE ALLOWED]: ";
        getline(cin >> ws, desig);
        while (valid_Name(desig))
        {
            cout << "\nERROR! SPACES WERE DETECTED IN NEW STUDENT DESIGNATION\n";
            cout << "\nPLEASE ENTER NEW STUDENT DESIGNATION AGAIN [NO SPACE ALLOWED]: ";
            getline(cin >> ws, desig);
        }

        for (int i = 0; i < user_index; i++)
        {
            if (id == users[i]->get_id())
            {
                cout << "\n*** ERROR! STUDENT MEMBER ALREADY EXIST WITH SIMILAR ID ***\n\n" << endl;
                exists = true;
            }
        }
        if (!exists)
        {
            users[user_index++] = new Staff(name, id, d, desig, l_db,type);
            cout << "\n*** NEW STUDENT MEMBER CREATED SUCCESSFULLY ***\n";
        }
        std::thread t(adminDelay);
        t.join();
    }

    return false;
}
// Function for user login
bool Library_Management_System::login_user()
{
    string name;
    int id;
    system("cls");
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t***** LIBRARY MANAGMENT SYSTEM PORTAL *****\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n\n\n";
    cout << "ENTER USER USERNAME [NO SPACE ALLOWED]: ";
    getline(cin >> ws, name);
    while (valid_Name(name))
    {
        cout << "\nERROR! SPACES WERE DETECTED IN USER USERNAME\n";
        cout << "\nPLEASE ENTER USER USERNAME AGAIN [NO SPACE ALLOWED]: ";
        getline(cin >> ws, name);
    }
    cout << "\nENTER USER ID [ID = 0 NOT ALLOWED]: ";
    while (!(cin >> id)) {
        cin.clear();  // Clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
        cout << "\nERROR! INVALID INPUT ENTERED, PLEASE ENTER AN INTEGER VALUE\n";
        cout << "\nPLEASE ENTER USER ID NUMBER AGAIN [ID = 0 NOT ALLOWED]: ";
    }

    while (valid_Id(id))
    {
        cout << "\nERROR! 0 WAS DETECTED IN USER ID\n";
        cout << "\nPLEASE ENTER USER ID NUMBER AGAIN [ID = 0 NOT ALLOWED]: ";
        cin >> id;
    }
    bool login = false;
    for (int i = 0; i < user_index; i++)
    {
        if (users[i]->verify(name, id))
        {
            login = true;
            cout << "\n\n***** LOGIN SUCCESSFULL, YOU WILL NOW BE REDIRECTED TO USER PORTAL IN A FEW SECONDS *****\n";
            std::thread t(librariandelay);
            t.join();
            system("cls");
            users[i]->user_panel(users[i]);
        }
    }
    if (!login)
        cout << "\n*** ERROR! USER DOES NOT EXIST IN DATABASE ***\n";
        std::thread t(adminDelay);
        t.join();

    return login;
}
