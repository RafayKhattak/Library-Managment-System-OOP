#pragma once
#include <string>
#include <iostream>
using namespace std;

class Book {
private:
    // Private data members
    string title;           // Title of the book
    string author;          // Author of the book
    string isbn;            // ISBN of the book
    bool is_reserved;       // Status indicating if the book is reserved
    bool is_borrowed;       // Status indicating if the book is borrowed
    string due_date;        // Due date for returning the book
    bool deleted_book;      // Status indicating if the book is deleted
    bool lost_book;         // Status indicating if the book is reported as lost

public:
    // Constructor
    Book();

    // Setter methods
    void set_deleted_book(bool t);
    void set_title(string t);
    void set_author(string a);
    void set_isbn(string i);
    void set_due_date(string dat);
    void set_borrowed(bool s);
    void set_lost_book(bool t);

    // Getter methods
    string get_title();
    string get_author();
    string get_isbn();
    string get_due_date();
    string get_is_reserved();

    // Display methods
    void show_due_date();
    void show_res_status();

    // Other methods
    bool book_request();    // Request to borrow the book
    void renew_info();      // Renew the book information
};
