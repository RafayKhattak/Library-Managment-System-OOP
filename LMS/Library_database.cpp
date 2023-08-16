#include"Library_database.h"
using namespace std;
// Constructor for Library_Database class
Library_Database::Library_Database()
{
	index = 0;
	books = new Book[200];
}
// Function to check if a string contains spaces
bool valid_namE(string admin_name)
{
    for (int i = 0; i < admin_name.length(); i++)
    {
        if (admin_name.at(i) == ' ')
        {
            return true;
        }
    }
    return false;
}
// Function to validate a date string in DD-MM-YY format
bool isValidDate(const std::string& dateString) {
    // Define a regular expression pattern for [DD-MM-YY] format
    std::regex pattern(R"((0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-\d{2})");

    // Use std::regex_match to check if the string matches the pattern
    if (!std::regex_match(dateString, pattern)) {
        return false;
    }

    // Additional checks for valid day and month values
    int day = std::stoi(dateString.substr(0, 2));
    int month = std::stoi(dateString.substr(3, 2));

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    else if (month == 2) {
        int year = std::stoi(dateString.substr(6, 2));
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if ((isLeapYear && day > 29) || (!isLeapYear && day > 28)) {
            return false;
        }
    }

    return true;
}
// Function to add a delay
void databasedelay()
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
// Function to add a delay for searching
void searchdelay()
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
}
// Function to get the current date as a string in DD-MM-YY format
std::string getCurrentDateAsString() {
    // Get the current system time
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    // Convert the time_point to a time_t object
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert the time_t object to a local time_tm struct using localtime
    std::tm* localTime = std::localtime(&currentTime);

    // Extract day, month, and year components from the local time_tm struct
    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1;     // Months are 0-based
    int year = localTime->tm_year + 1900;  // Years since 1900

    // Create a string in the format DD-MM-YY
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << day << "-"
        << std::setfill('0') << std::setw(2) << month << "-"
        << std::setfill('0') << std::setw(2) << (year % 100);

    return oss.str();
}
// Function to calculate the return date based on user type
std::string calculateReturnDate(const std::string& currentDate, const std::string& type) {
    std::tm date = {};
    std::istringstream iss(currentDate);
    iss >> std::get_time(&date, "%d-%m-%y");

    int weeksToAdd = 0;
    if (type == "staff") {
        weeksToAdd = 16;
    }
    else if (type == "student") {
        weeksToAdd = 2;
    }

    std::chrono::system_clock::time_point returnTime = std::chrono::system_clock::from_time_t(std::mktime(&date));
    returnTime += std::chrono::hours(24 * 7 * weeksToAdd); // Convert weeks to hours

    std::time_t returnDate = std::chrono::system_clock::to_time_t(returnTime);
    std::tm* localReturnTime = std::localtime(&returnDate);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << localReturnTime->tm_mday << "-"
        << std::setfill('0') << std::setw(2) << (localReturnTime->tm_mon + 1) << "-"
        << std::setfill('0') << std::setw(2) << (localReturnTime->tm_year % 100);

    return oss.str();
}
// Function to add a book to the database
bool Library_Database::add() {
    string title, author, isbn;
    system("cls");
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\t***** LIBRARIAN PORTAL *****\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n\n\n";
    cout << "ENTER BOOK TITLE [_ INSTEAD OF SPACE]: ";
    getline(cin >> ws, title);
    while (valid_namE(title))
    {
        cout << "\nERROR! SPACES WERE DETECTED IN BOOK TITLE\n";
        cout << "\nPLEASE ENTER BOOK TITLE AGAIN [_ INSTEAD OF SPACE]: ";
        getline(cin >> ws, title);
    }
    cout << "\nENTER BOOK AUTHOR NAME [_ INSTEAD OF SPACE]: ";
    getline(cin >> ws, author);
    while (valid_namE(author))
    {
        cout << "\nERROR! SPACES WERE DETECTED IN BOOK AUTHOR NAME\n";
        cout << "\nPLEASE ENTER BOOK AUTHOR NAME AGAIN [_ INSTEAD OF SPACE]: ";
        getline(cin >> ws, author);
    }
    cout << "\nENTER ISBN [NO SPACE ALLOWED]: ";
    getline(cin >> ws, isbn);
    while (valid_namE(isbn))
    {
        cout << "\nERROR! SPACES WERE DETECTED IN BOOK ISBN\n";
        cout << "\nPLEASE ENTER ISBN [NO SPACE ALLOWED]: ";
        getline(cin >> ws, isbn);
    }
    bool exists = false;;
    for (int i = 0; i < index; i++)
    {
        if (books[i].get_isbn() == isbn)
        {
            cout << "\nERROR! BOOK WITH SIMILAR ISBN ALREADY EXISTS!\n";
            exists = true;
        }
    }
    if (!exists)
    {
        books[index].set_title(title);
        books[index].set_author(author);
        books[index].set_borrowed(false);
        books[index].set_deleted_book(false);
        books[index].set_due_date("N/A");
        books[index++].set_isbn(isbn);
        cout << "\nA NEW BOOK HAS BEEN ADDED SUCCESSFULLY";
    }
    std::thread t(databasedelay);
    t.join();
    system("cls");
    return !exists;
}
// Function to display books for users
void Library_Database::displayuser() 
{
    cout << "---------------------------------------------------------------------\n";
    cout << "TITLE          AUTHOR         ISBN           STATUS         DUE DATE" << endl;
    cout << "---------------------------------------------------------------------\n";
    for (int i = 0; i < index; i++)
    {
        cout << std::left << setw(15) << books[i].get_title() << setw(15) << books[i].get_author() << setw(15) << books[i].get_isbn() << setw(15) << books[i].get_is_reserved() << setw(15) << books[i].get_due_date() << endl;
    }
    cout << "---------------------------------------------------------------------\n";
    cout << endl;
}
// Function to display all books in the database
void Library_Database::display() {
    char option;
    system("cls");
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\t***** LIBRARIAN PORTAL *****\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n\n\n";
    cout << "TITLE          AUTHOR         ISBN           STATUS         DUE DATE" << endl;
    for (int i = 0; i < index; i++)
    {
        cout << std::left << setw(15) << books[i].get_title() << setw(15) << books[i].get_author() << setw(15) << books[i].get_isbn() << setw(15) << books[i].get_is_reserved() << setw(15) << books[i].get_due_date() << endl;
    }
    cout << "\nDO YOU WANT TO GO BACK?\n\n";
    cout << "ENTER [Y/y] HERE: ";
    cin >> option;
    while (option != 'Y' && option != 'y')
    {
        cout << "\nERROR! INVALID INPUT ENTERED, PLEASE TRY AGAIN.\n";
        cout << "\nENTER [Y/y] HERE: ";
        cin >> option;
    }
    if (option == 'Y' || option == 'y')
    {
        system("cls");
        return;
    }
}
// Function to update book information
bool Library_Database::update() { 
    string query;
    int choice;
    string ans;
    int status;
    bool loop = true;
    bool exists = false;
    system("cls");
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\t***** LIBRARIAN PORTAL *****\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n\n\n";
    cout << "ENTER BOOK TITLE OR ISBN [NO SPACE ALLOWED USE _ INSTEAD]: ";
    getline(cin >> ws, query);
    while (valid_namE(query))
    {
        cout << "\nERROR! SPACES WERE DETECTED IN BOOK TITLE/ISBN\n";
        cout << "\nPLEASE ENTER BOOK TITLE OR ISBN AGAIN [NO SPACE ALLOWED USE _ INSTEAD]: ";
        getline(cin >> ws, query);
    }
    
    for (int i = 0; i < index; i++)
    {
        if (books[i].get_isbn() == query || books[i].get_title() == query)
        {
            cout << "\n*** BOOK FOUND SUCCESSFULLY ***\n\n";
            exists = true;
            std::thread t(databasedelay);
            t.join();
            //add a delay here then clear screen
            while (loop) {
                system("cls");
                cout << "------------------------------------------------------------------------------------------------------------------------\n";
                cout << "\t\t\t\t\t\t***** LIBRARIAN PORTAL *****\n";
                cout << "------------------------------------------------------------------------------------------------------------------------\n\n\n";
                cout << "WHAT DO YOU WANT TO CHANGE?\n\n";
                cout << "[1] TITLE\n\n";
                cout << "[2] AUTHOR\n\n";
                cout << "[3] ISBN\n\n";
                cout << "[4] STATUS\n\n"; 
                cout << "[5] DUE DATE\n\n";
                cout << "[6] GO BACK\n\n";
                cout << "ENTER YOUR OPTION HERE: ";
                while (!(cin >> choice) && (choice >= 1 && choice <= 5)) {
                    cin.clear();  // Clear the error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
                    cout << "\nERROR! INVALID INPUT ENTERED, PLEASE ENTER GIVEN INTEGER VALUE\n";
                    cout << "\nENTER YOUR CHOICE HERE: ";
                }
                switch (choice)
                {
                case 1:
                    cout << "\nENTER BOOK NEW TITLE [_ INSTEAD OF SPACE]: ";
                    getline(cin >> ws, ans);
                    while (valid_namE(ans))
                    {
                        cout << "\nERROR! SPACES WERE DETECTED IN BOOK NEW TITLE\n\n";
                        cout << "\nPLEASE ENTER BOOK NEW TITLE AGAIN [_ INSTEAD OF SPACE]: ";
                        getline(cin >> ws, ans);
                    }
                    books[i].set_title(ans);
                    cout << "\n*** BOOK TITLE CHANGED SUCCESSFULLY ***\n\n";
                    {std::thread t(databasedelay);
                    t.join(); }
                    break;
                case 2:
                    cout << "\nENTER BOOK AUTHOR NEW NAME [_ INSTEAD OF SPACE]: ";
                    getline(cin >> ws, ans);
                    while (valid_namE(ans))
                    {
                        cout << "\nERROR! SPACES WERE DETECTED IN BOOK AUTHOR NEW NAME\n\n";
                        cout << "\nPLEASE ENTER BOOK AUTHOR NEW NAME AGAIN [_ INSTEAD OF SPACE]: ";
                        getline(cin >> ws, ans);
                    }
                    books[i].set_author(ans);
                    cout << "\n*** BOOK AUTHOR NAME CHANGED SUCCESSFULLY ***\n\n";
                    {std::thread t(databasedelay);
                    t.join(); }
                    break;
                case 3:
                    cout << "\nENTER NEW ISBN [NO SPACE ALLOWED]: ";
                    getline(cin >> ws, ans);
                    while (valid_namE(ans))
                    {
                        cout << "\nERROR! SPACES WERE DETECTED IN BOOK NEW ISBN\n\n";
                        cout << "\nPLEASE ENTER NEW ISBN [NO SPACE ALLOWED]: ";
                        getline(cin >> ws, ans);
                    }
                    books[i].set_isbn(ans);
                    cout << "\n*** BOOK ISBN CHANGED SUCCESSFULLY ***\n\n";
                    {std::thread t(databasedelay);
                    t.join(); }
                    break;
                case 4:
                    cout << "\nENTER NEW STATUS FOR THE BOOK\n";
                    cout << "[1] AVAILABLE\n";
                    cout << "[2] BORROWED\n";
                    cout << "\nENTER YOUR OPTION HERE: ";
                    while (!(cin >> status) && (choice >= 1 && choice <= 2)) {
                        cin.clear();  // Clear the error state
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
                        cout << "\nERROR! INVALID INPUT ENTERED, PLEASE ENTER AN INTEGER VALUE\n\n";
                        cout << "\nENTER YOUR CHOICE HERE: ";
                    }
                    if (status == 1)
                    {
                        books[i].set_borrowed(false);
                    }
                    else {
                        books[i].set_borrowed(true);
                    }
                    cout << "\n*** BOOK STATUS CHANGED SUCCESSFULLY ***\n\n";
                    {std::thread t(databasedelay);
                    t.join(); }
                    break;
                case 5:
                    cout << "\nENTER NEW DUE DATE FOR THE BOOK [NO SPACE ALLOWED,[DD-MM-YY](15-08-23): ";
                    getline(cin >> ws, ans);
                    while (valid_namE(ans))
                    {
                        cout << "\nERROR! SPACES WERE DETECTED IN NEW DUE DATE\n\n";
                        cout << "\nPLEASE ENTER NEW DUE DATE FOR THE BOOK AGAIN [NO SPACE ALLOWED, [DD-MM-YY](15-08-23): ";
                        getline(cin >> ws, ans);
                    }
                    while (!isValidDate(ans))
                    {
                        cout << "\nERROR! INVALID FORMAT WAS DETECTED\n\n";
                        cout << "\nPLEASE ENTER NEW DUE DATE FOR THE BOOK AGAIN [NO SPACE ALLOWED, [DD-MM-YY](15-08-23): ";
                        getline(cin >> ws, ans);
                    }
                    books[i].set_due_date(ans);
                    cout << "\n*** DUE DATE CHANGED SUCCESSFULLY ***\n\n";
                    {std::thread t(databasedelay);
                    t.join(); }
                    break;
                case 6:
                    loop = false;
                    system("cls");
                    break;
                }
            }
        }
        else {
            cout << "\n*** ERROR, BOOK DOES NOT EXIST IN THE DATABASE ***\n";
            return exists;
        }
    }
    return exists;
}
// Function to delete a book from the database
bool Library_Database::Delete() {
    string query;
    bool loop = true;
    bool exists = false;
    system("cls");
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\t***** LIBRARIAN PORTAL *****\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n\n\n";
    cout << "ENTER BOOK TITLE OR ISBN [NO SPACE ALLOWED USE _ INSTEAD]: ";
    getline(cin >> ws, query);
    while (valid_namE(query))
    {
        cout << "\nERROR! SPACES WERE DETECTED IN BOOK TITLE/ISBN\n";
        cout << "\nPLEASE ENTER BOOK TITLE OR ISBN AGAIN [NO SPACE ALLOWED USE _ INSTEAD]: ";
        getline(cin >> ws, query);
    }
    for (int i = 0; i < index; i++)
    {
        if (books[i].get_isbn() == query || books[i].get_title() == query)
        {
            exists = true;
            books[i].set_author("N/A");
            books[i].set_borrowed(false);
            books[i].set_deleted_book(true);
            books[i].set_due_date("N/A");
            books[i].set_isbn("N/A");
            books[i].set_title("N/A");
            cout << "\n*** BOOK DELETED SUCCESSFULLY ***\n\n";
            std::thread t(databasedelay);
            t.join();
            return true;
        }
        else {
            cout << "\n*** ERROR! BOOK DOES NOT EXIST IN DATABASE ***\n";
            std::thread t(databasedelay);
            t.join();
            return false;
        }
    }
    return exists;
}
// Function to search for a book in the database for the user
bool Library_Database::searchuser() {
    string isbn;
    cout << endl;
    cout << "ENTER BOOK TITLE OR ISBN [NO SPACES ALLOWED, ADD _ INSTEAD]: ";
    getline(cin >> ws, isbn);
    while (valid_namE(isbn))
    {
        cout << "\nERROR! SPACES WERE DETECTED IN BOOK TITLE OR ISBN\n\n";
        cout << "\nPLEASE ENTER BOOK TITLE OR ISBN AGAIN [NO SPACES ALLOWED, ADD _ INSTEAD]: ";
        getline(cin >> ws, isbn);
    }
    bool exists = false;;
    for (int i = 0; i < index; i++)
    {
        if (books[i].get_isbn() == isbn || books[i].get_title() == isbn)
        {
            cout << "\n==========================================================\n";
            cout << "| BOOK EXISTS IN THE DATABASE WITH THE STATUS: " << books[i].get_is_reserved() << " |\n";
            cout << "==========================================================\n\n";
            exists = true;
            break;
        }
    }
    if (!exists)
        cout << "\n*** ERROR! THE BOOK DOES NOT EXIST IN THE DATABASE ***\n\n";
    return exists;
}
// Function to search for a book in the database
bool Library_Database::search() {
    string isbn;
    system("cls");
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\t***** LIBRARIAN PORTAL *****\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n\n\n";
    cout << "ENTER BOOK TITLE OR ISBN [NO SPACES ALLOWED, ADD _ INSTEAD]: ";
    getline(cin >> ws, isbn);
    while (valid_namE(isbn))
    {
        cout << "\nERROR! SPACES WERE DETECTED IN BOOK TITLE OR ISBN\n";
        cout << "\nPLEASE ENTER BOOK TITLE OR ISBN AGAIN [NO SPACES ALLOWED, ADD _ INSTEAD]: ";
        getline(cin >> ws, isbn);
    }
    bool exists = false;;
    for (int i = 0; i < index; i++)
    {
        if (books[i].get_isbn() == isbn || books[i].get_title() == isbn)
        {
            cout << "\nBOOK EXISTS IN THE DATABASE WITH THE STATUS: " << books[i].get_is_reserved() << endl;
            exists = true;
        }
    }
    if (!exists)
        cout << "\nERROR! THE BOOK DOES NOT EXIST IN THE DATABASE\n";
    std::thread t(searchdelay);
    t.join();
    system("cls");
    return exists;
}
// Function to borrow a book
Book* Library_Database::borrow_book(string s)
{
    string isbn;
    cout << "\nENTER BOOK TITLE OR ISBN [NO SPACE ALLOWED, USE _ INSTEAD]: ";
    getline(cin >> ws, isbn);
    while (valid_namE(isbn))
    {
        cout << "\nERROR! SPACES WERE DETECTED IN BOOK TITLE OR ISBN\n";
        cout << "\nPLEASE ENTER BOOK TITLE OR ISBN AGAIN [NO SPACES ALLOWED, ADD _ INSTEAD]: ";
        getline(cin >> ws, isbn);
    }
    Book* ptr = nullptr;
    bool exists = false;;
    for (int i = 0; i < index; i++)
    {
        if (books[i].get_isbn() == isbn || books[i].get_title() == isbn)
        {
            if (books[i].book_request()) {
                books[i].set_borrowed(true);
                ptr = &books[i];
            }
            string currentDate = getCurrentDateAsString();
            string returnDate = calculateReturnDate(currentDate, s);
            books[i].set_due_date(returnDate);
            exists = true;
            break;
        }
    }
    if (!exists)
        cout << "\n*** ERROR! BOOK DOES NOT EXIST IN THE DATABASE ***\n";
    return ptr;
}