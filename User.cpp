#include "User.h"
#include "Book.h"

string User::get_user_id()
{
    return user_id;
}

string User::get_name()
{
    return name;
}

string User::get_username()
{
    return username;
}

string User::get_password()
{
    return password;
}

void User::set_user_id(string user_id)
{
    this->user_id = user_id;
}

void User::set_name(string name)
{
    this->name = name;
}

void User::set_username(string username)
{
    this->username = username;
}

void User::set_password(string password)
{
    this->password = password;
}

string Student::get_student_id()
{
    return student_id;
}

string Student::get_student_class()
{
    return student_class;
}

string Student::get_school()
{
    return school;
}

string Student::get_borrowed_books()
{
    return borrowed_books;
}

void Student::set_student_id(string student_id)
{
    this->student_id = student_id;
}

void Student::set_student_class(string student_class)
{
    this->student_class = student_class;
}

void Student::set_school(string school)
{
    this->school = school;
}

void Student::set_borrowed_books(string borrowed_books)
{
    this->borrowed_books = borrowed_books;
}

void Student::borrow_book(Book *book)
{
    if(borrowed_books == "0;")
        borrowed_books = "";
    borrowed_books += book->get_book_id() + ";";
    this->set_borrowed_books(borrowed_books);
}

string Librarian::get_staff_id()
{
    return staff_id;
}

void Librarian::set_staff_id(string staff_id)
{
    this->staff_id = staff_id;
}
