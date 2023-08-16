#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include <string>
#include <iostream>
#include <regex>
#include <thread>
#include <chrono>
#include <ctime>
#include <iomanip> // For std::setw
#include <sstream> // For std::ostringstream
using namespace std;

class Library_Database {
private:
    int index;   // Index to keep track of the number of books in the database
    Book* books; // Array of books to store the book records
public:
    Library_Database(); // Constructor for initializing the database
    bool add();         // Function to add a new book to the database
    void display();     // Function to display all books in the database
    void displayuser(); // Function to display user-specific book information
    bool update();      // Function to update the information of an existing book
    bool Delete();      // Function to delete a book from the database
    bool search();      // Function to search for a book by various criteria
    bool searchuser();  // Function to search for a book by criteria suitable for users
    Book* borrow_book(string s); // Function to borrow a book from the database
};
