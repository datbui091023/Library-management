#pragma once
#ifndef BOOK_H
#define BOOK_H

#include<string>
#include<vector>
#include<iostream>
#include <ctime>

using namespace std;

class Date;

class Book
{
public:
private:
    string book_id;
    string title;
    string author;
    string genre;
    string isbn;
    string currentStatus; // {Available, Borrowed}
    int quantity;
    int available_copies;

    time_t borrowDate;
    time_t dueDate;
    time_t returnDate;
public:
    Book() 
    {
        this->currentStatus = "Available";
    }

    //Constructor for testing
    Book(string id, string title, string author,int quantity)
    {
        this->book_id = id;
        this->title = title;
        this->author = author;
        this->genre = genre;
        this->isbn = isbn;
        this->quantity = quantity;
        this->available_copies = quantity;
        this->currentStatus = "Available";
        this->borrowDate = 0;
        this->dueDate = 0;
        this->returnDate = 0;
    }

    //Getters
    string get_book_id();
    string get_title();
    string get_author();
    string get_genre();
    string get_isbn();
    int get_quantity();
    int get_available_copies();
    string getStatus();

    //Setters
    void set_book_id(string);
    void set_title(string);
    void set_author(string);
    void set_genre(string);
    void set_isbn(string);
    void set_quantity(int);

    bool isAvailable();
    void borrow_books();
    void return_book();

    friend double calculate_fine(Book& book);
};
#endif // !BOOK_H