#include "Account.h"
using namespace std;

// Function to check if a name contains spaces
bool valid_Name_ACC(string name)
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

// Constructor
Account::Account() {
    books_borrowed = new Book * [100];
    no_borrowed_books = 0;
    no_lost_books = 0;
    no_reserved_books = 0;
    fine_amount = 0;
}

// Setter methods for the number of borrowed, lost, and reserved books
void Account::set_n_borrowed(int n) { no_borrowed_books = n; }
void Account::set_n_lost(int n) { no_lost_books = n; }
void Account::set_n_reserved(int n) { no_reserved_books = n; }

// Borrow a book
bool Account::borrow(Book* book) {
    if (book != nullptr) {
        books_borrowed[no_borrowed_books++] = book;
        return true;
    }
    return false;
}

// Display borrowed book information
void Account::display() {
    cout << "----------------------------------------------------------------------\n";
    cout << "Title          Author         ISBN           Status         Due Date" << "\n";
    cout << "----------------------------------------------------------------------\n";
    for (int i = 0; i < no_borrowed_books; i++)
    {
        cout << std::left << setw(15) << books_borrowed[i]->get_title() << setw(15) << books_borrowed[i]->get_author() << setw(15) << books_borrowed[i]->get_isbn() << setw(15) << books_borrowed[i]->get_is_reserved() << setw(15) << books_borrowed[i]->get_due_date() << endl;
    }
    cout << "----------------------------------------------------------------------\n\n";
}

// Calculate fine for late returns
void Account::calculate_fine() {
    cout << "\n==========================\n";
    cout << "| FINE AMOUNT: " << setw(9) << fine_amount << " |\n";
    cout << "==========================\n\n";
}

// Getter methods for the number of borrowed, lost, and reserved books
int Account::get_n_borrowed() {
    return no_borrowed_books;
}
int Account::get_n_lost() {
    return no_lost_books;
}
int Account::get_n_reserved() {
    return no_reserved_books;
}

// Return a borrowed book
bool Account::return_book(string isbn) {
    for (int i = 0; i < no_borrowed_books; i++)
    {
        if (isbn == books_borrowed[i]->get_isbn())
        {
            books_borrowed[i]->renew_info();
            for (int ind = i; ind < no_borrowed_books; ind++)
            {
                books_borrowed[ind] = books_borrowed[ind + 1];
            }
            no_borrowed_books--;
            return true;
        }
    }
    cout << "\n*** ERROR! INVALID ISBN ***\n\n";
    return false;
}

// Report a book as lost
bool Account::report_loss()
{
    display();
    cout << "ENTER ISBN OF THE BOOK YOU WANT TO REPORT FOR LOST [NO SPACE ALLOWED]: ";
    string isbn;
    getline(cin >> ws, isbn);
    while (valid_Name_ACC(isbn))
    {
        cout << "\nERROR! SPACES WERE DETECTED IN BOOK ISBN\n\n";
        cout << "\nPLEASE ENTER ISBN OF BOOK YOU WANT TO REPORT FOR LOST AGAIN [NO SPACE ALLOWED]: ";
        getline(cin >> ws, isbn);
    }
    for (int i = 0; i < no_borrowed_books; i++)
    {
        if (isbn == books_borrowed[i]->get_isbn())
        {
            no_lost_books++;
            books_borrowed[i]->set_lost_book(true);
            books_borrowed[i]->set_due_date("N/A");
            for (int ind = i; ind < no_borrowed_books; ind++)
            {
                books_borrowed[ind] = books_borrowed[ind + 1];
            }
            no_borrowed_books--;
            fine_amount += 2000;
            return true;
        }
    }
    cout << "\n*** ERROR! INVALID ISBN ***\n\n";
    return false;
}
