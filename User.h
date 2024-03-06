#pragma once
#ifndef USER_H
#define USER_H

#include<string>
#include<vector>
#include<iostream>

using namespace std;

class Book;

class User
{
private: 
    string user_id;
    string name;
    string username;
    string password;
public:
    User() {}

    string get_user_id();
    string get_name();
    string get_username();
    string get_password();

    void set_user_id(string user_id);
    void set_name(string name);
    void set_username(string username);
    void set_password(string password);
};

class Student : public User
{
private:
    string student_id;
    string student_class;
    string school;
    string borrowed_books;
public:
    Student() {borrowed_books = "0;";}

    string get_student_id();
    string get_student_class();
    string get_school();
    string get_borrowed_books();

    void set_student_id(string student_id);
    void set_student_class(string student_class);
    void set_school(string school);
    void set_borrowed_books(string borrowed_books);

    void borrow_book(Book* book);
};


class Librarian : public User
{
private:
    string staff_id;
public:
    Librarian() {}

    string get_staff_id();

    void set_staff_id(string staff_id);
};
#endif // !USER_H