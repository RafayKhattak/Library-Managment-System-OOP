#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include "Book.h"
using namespace std;

class Account {
private:
    Book** books_borrowed;      // Array to store borrowed books
    int no_borrowed_books;      // Number of borrowed books
    int no_lost_books;          // Number of lost books
    int no_reserved_books;      // Number of reserved books
    float fine_amount;          // Amount of fine for late returns

public:
    // Constructor
    Account();

    // Setter methods for the number of borrowed, lost, and reserved books
    void set_n_borrowed(int n);
    void set_n_lost(int n);
    void set_n_reserved(int n);

    // Borrow a book
    bool borrow(Book* book);

    // Display borrowed and reserved book information
    void display();

    // Calculate fine for late returns
    void calculate_fine();

    // Getter methods for the number of borrowed, lost, and reserved books
    int get_n_borrowed();
    int get_n_lost();
    int get_n_reserved();

    // Return a borrowed book
    bool return_book(string isbn);

    // Report a book as lost
    bool report_loss();
};
