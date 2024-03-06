#pragma once
#ifndef LIBRARY_H
#define LIBRARY_H

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<iomanip>

class Book;
class User;
class Student;
class Librarian;

using namespace std;

class Library
{
private:
    vector<Book *> books;
    vector<Student*> students;
    vector<Librarian*> librarians;
public:
    Library() {}

    void addBook(Book *newbook);
    void removeBook(string _id);
    void addStudent(Student *newstudent);
    void removeStudent(string &student_id);

    void addLibrarian(Librarian *newlibrarian);
    void removeLibrarian(string &librarian_id);

    vector<Student*> getStudents();
    vector<Librarian*> getLibrarians();

    void setStudents(vector<Student*> students);
    void setLibrarians(vector<Librarian*> librarians);
    void displayBooks();

    void updateStudent(vector <Student*> &students);
    void updateBook();
    void updateLibrarian();

    void readStudentFile(vector <Student*> &students);
    void readBookFile();
    void readLibrarianFile(vector <Librarian*> &librarians);

    Book* findBookById(string _id);
    Student* findStudentById(string _id);

    void StudentLogin(Student* &students);
    void LibrarianLogin(Librarian* &librarians);
};  

#endif // !LIBRARY_H