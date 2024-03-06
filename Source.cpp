#include "Book.h"
#include "User.h"
#include "Library.h"
#include <limits>
#include <conio.h>
#include <sstream>
#include <algorithm>
using namespace std;

void StudentRegister(Library &Time);
void LibrarianRegister(Library &Time);
void StudentLogin(Library &Time, Student *&_student);
void Delay(int second);

void Menu()
{
    cout << "1.Register" << endl;
    cout << "2.Login" << endl;
    cout << "3.Exit" << endl;
}

void StudentMenu()
{
    cout << "1.Borrow book" << endl;
    cout << "2.Return book" << endl;
    cout << "3.Display borrowed books" << endl;
    cout << "4.Display all books" << endl;
    cout << "5.Logout" << endl;
}

void LibrarianMenu()
{
    cout << "1.Add book" << endl;
    cout << "2.Remove book" << endl;
    cout << "3.Add student" << endl;
    cout << "4.Remove student" << endl;
    cout << "5.Display all books" << endl;
    cout << "6.Display all students" << endl;
    cout << "7.Reports" << endl;
    cout << "8.Logout" << endl;
}

int main()
{
    Library Time;

    Book *book1 = new Book("1", "Harry Potter", "J.K.Rowling", 10);
    Book *book2 = new Book("2", "The Lord of the Rings", "J.R.R.Tolkien", 10);
    Book *book3 = new Book("3", "The Hobbit", "J.R.R.Tolkien", 10);
    Book *book4 = new Book("4", "The Hunger Games", "Suzanne Collins", 10);

    Time.addBook(book1);
    Time.addBook(book2);
    Time.addBook(book3);
    Time.addBook(book4);

    system("cls");

    int choice = 0;

    while (true)
    {
        Menu();
        cout << "Enter your choice: ";
        cin >> choice;
        system("cls");
        if (choice == 1)
        {
            cout << "Register as: " << endl;
            cout << "1.Student" << endl;
            cout << "2.Librarian" << endl;
            cout << "Enter your choice: ";
            int choice1 = 0;
            cin >> choice1;
            system("cls");
            if (choice1 == 1)
            {
                cin.ignore();
                StudentRegister(Time);
                // vector<Student *> newstudents = Time.getStudents();
                // for (auto student : newstudents)
                // {
                //     cout << student->get_name() << endl;
                //     cout << student->get_user_id() << endl;
                //     cout << student->get_username() << endl;
                //     cout << student->get_password() << endl;
                //     cout << student->get_student_id() << endl;
                //     cout << student->get_student_class() << endl;
                // }
                Delay(2);
                system("cls");
            }
            else if (choice1 == 2)
            {
                cin.ignore();
                LibrarianRegister(Time);
                Delay(2);
                system("cls");
            }
            else
            {
                cout << "Invalid choice!" << endl;
                Delay(2);
                system("cls");
            }
        }

        else if (choice == 2)
        {
            cout << "Login as: " << endl;
            cout << "1.Student" << endl;
            cout << "2.Librarian" << endl;
            cout << "Enter your choice: ";
            int choice2 = 0;
            cin >> choice2;
            system("cls");
            if (choice2 == 1)
            {
                vector<Student *> students;
                Time.readStudentFile(students);
                Student *_student = nullptr;
                cin.ignore();
                Time.StudentLogin(_student);
                Delay(2);
                system("cls");
                if (_student != nullptr)
                {

                    while (true)
                    {
                        int choice3 = 0;
                        StudentMenu();
                        cout << "Enter your choice: ";
                        cin >> choice3;
                        system("cls");
                        if (choice3 == 1) // Borrow book
                        {
                            // Time.readStudentFile(students);
                            cout << "How many books do you want to borrow?(maximum is 3): ";
                            int num;
                            cin >> num;
                            cin.ignore();
                            if (num > 3)
                            {
                                do
                                {
                                    cout << "Please enter a number between 1 and 3: ";
                                    cin >> num;
                                } while (num > 3 || num < 1);
                            }
                            for (int i = 0; i < num; i++)
                            {
                                string book_id;
                                cout << "Enter book id: ";
                                cin >> book_id;
                                Book *book = Time.findBookById(book_id);
                                if (book != nullptr)
                                {
                                    _student->borrow_book(book);
                                    book->borrow_books();
                                    cout << _student->get_borrowed_books() << endl;
                                    Time.updateStudent(students);
                                }
                                else
                                {
                                    cout << "Book not found!" << endl;
                                    i--;
                                }
                            }
                            // update the vector to the file

                            Delay(2);
                            cout << "Press any key to continue...";
                            getch();
                            system("cls");
                        }

                        else if (choice3 == 2) // Return book
                        {
                            cout << "How many books do you want to return?(maximum is 3): ";
                            int num = 0;
                            cin >> num;
                            if (num > 3)
                            {
                                do
                                {
                                    cout << "Please enter a number between 1 and 3: ";
                                    cin >> num;
                                } while (num > 3 || num < 1);
                            }

                            for (int i = 0; i < num; ++i)
                            {
                                string book_id;
                                cout << "Enter book id: ";
                                cin >> book_id;
                                Book *book = Time.findBookById(book_id);
                                if (book != nullptr)
                                {
                                    book->return_book();
                                    string removeFromBorrowedBooks = book->get_book_id() + ";";
                                    size_t found = _student->get_borrowed_books().find(removeFromBorrowedBooks);
                                    if (found != string::npos)
                                    {
                                        _student->set_borrowed_books(_student->get_borrowed_books().erase(found, removeFromBorrowedBooks.length()));
                                    }
                                    if (_student->get_borrowed_books() == "")
                                        _student->set_borrowed_books("0;");
                                    cout << "Returned successfully!" << endl;
                                }
                                else
                                {
                                    cout << "Book not found!" << endl;
                                    i--;
                                }
                            }
                            Time.updateStudent(students); // update the vector to the file
                            Delay(2);
                            cout << "Press any key to continue...";
                            getch();
                            system("cls");
                        }

                        else if (choice3 == 3) // Display borrowed books
                        {
                            if (_student->get_borrowed_books() == "0;")
                                cout << "You have not borrowed any books!" << endl;
                            else
                            {
                                cout << "Borrowed books:" << endl;
                                string _borrowedBooks = _student->get_borrowed_books();
                                stringstream ss(_borrowedBooks);
                                string token;
                                while (getline(ss, token, ';'))
                                {
                                    Book *book = Time.findBookById(token);
                                    cout << book->get_title() << endl;
                                }
                            }
                            Delay(2);
                            cout << "Press any key to continue...";
                            getch();
                            system("cls");
                        }

                        else if (choice3 == 4) // Display all books
                        {
                            Time.displayBooks();
                            Delay(2);
                            cout << "Press any key to continue...";
                            getch();
                            system("cls");
                        }

                        else if (choice3 == 5)
                        {
                            break;
                        }
                        else
                        {
                            cout << "Invalid choice!" << endl;
                            cout << "Press any key to continue...";
                            getch();
                            system("cls");
                        }
                    }
                }
                else
                {
                    // cout << "Login failed!" << endl;
                    Delay(2);
                    system("cls");
                }
            }
            if (choice2 == 2)
            {
                vector<Librarian *> librarians;
                Time.readLibrarianFile(librarians);
                Librarian *_librarian = nullptr;
                cin.ignore();
                Time.LibrarianLogin(_librarian);
                if (_librarian != nullptr)
                {

                    Delay(2);
                    cout << "Press any key to continue...";
                    getch();
                    system("cls");
                    while (true)
                    {
                        LibrarianMenu();
                        int choice4 = 0;
                        cout << "Enter your choice: ";
                        cin >> choice4;
                        system("cls");
                        if (choice4 == 1) // Add book
                        {
                            string book_id, title, author, isbn;
                            int quantity;
                            cout << "Enter book id: ";
                            cin >> book_id;
                            cout << "Enter title: ";
                            cin.ignore();
                            getline(cin, title);
                            cout << "Enter author: ";
                            getline(cin, author);
                            cout << "Enter isbn: ";
                            getline(cin, isbn);
                            cout << "Enter quantity: ";
                            cin >> quantity;

                            Book *newbook = new Book;
                            newbook->set_book_id(book_id);
                            newbook->set_title(title);
                            newbook->set_author(author);
                            newbook->set_isbn(isbn);
                            newbook->set_quantity(quantity);

                            Time.addBook(newbook);
                            Delay(2);
                            cout << "Press any key to continue...";
                            getch();
                            system("cls");
                        }

                        else if (choice4 == 2) // Remove book
                        {
                            string book_id;
                            cout << "Enter book id: ";
                            cin >> book_id;
                            Book *book = Time.findBookById(book_id);
                            if (book != nullptr)
                            {
                                Time.removeBook(book_id);
                                Time.updateBook();
                                cout << "Removed successfully!" << endl;
                            }
                            else
                            {
                                cout << "Book not found!" << endl;
                            }
                            Delay(2);
                            cout << "Press any key to continue...";
                            getch();
                            system("cls");
                        }

                        else if (choice4 == 3) // Add student
                        {
                            cin.ignore();
                            string userid, name, username, password, student_id, student_class, school;
                            // Time.readStudentFile();
                            // vector<Student *> students = Time.getStudents();

                            cout << "Enter your user id: ";
                            getline(cin, userid);
                            // for (auto student : students)
                            // {
                            //     if (student->get_user_id() == userid)
                            //     {
                            //         cout << "This user id is already existed!" << endl;
                            //         return;
                            //     }
                            // }

                            cout << "Enter your name: ";
                            getline(cin, name);
                            cout << "Enter your username: ";
                            getline(cin, username);
                            cout << "Enter your password: ";
                            getline(cin, password);
                            cout << "Enter your student id: ";
                            getline(cin, student_id);
                            cout << "Enter your class: ";
                            getline(cin, student_class);
                            cout << "Enter your school: ";
                            getline(cin, school);

                            // cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            // write to file
                            fstream fout;
                            fout.open("C:\\Users\\PC\\Desktop\\Final of final\\StudentAccount.csv", ios::out | ios::app);
                            fout << userid << ","
                                 << name << ","
                                 << username << ","
                                 << password << ","
                                 << student_id << ","
                                 << student_class << ","
                                 << school << ","
                                 << "0;" << endl;
                            fout.close();

                            // add to vector
                            Student *newstudent = new Student;
                            newstudent->set_user_id(userid);
                            newstudent->set_name(name);
                            newstudent->set_username(username);
                            newstudent->set_password(password);
                            newstudent->set_student_id(student_id);
                            newstudent->set_student_class(student_class);
                            newstudent->set_school(school);
                            Time.addStudent(newstudent);
                            cout << "Student added successfully!" << endl;
                            Delay(2);
                            cout << "Press any key to continue...";
                            getch();
                            system("cls");
                        }

                        else if (choice4 == 4) // Remove student
                        {
                            vector<Student *> newstudents = Time.getStudents();
                            Time.readStudentFile(newstudents);
                            if (newstudents.size() == 0)
                            {
                                cout << "There is no student in the library!" << endl;
                                Delay(2);
                                cout << "Press any key to continue...";
                                getch();
                                system("cls");
                                continue;
                            }
                            string student_id;
                            cout << "Enter student id: ";
                            cin >> student_id;
                            Student *student = Time.findStudentById(student_id);
                            if (student != nullptr)
                            {
                                Time.removeStudent(student_id);
                                Time.setStudents(Time.getStudents());
                                vector<Student *> students = Time.getStudents();
                                Time.updateStudent(students);
                                cout << "Removed successfully!" << endl;
                            }
                            else
                            {
                                cout << "Student not found!" << endl;
                            }

                            Delay(2);
                            cout << "Press any key to continue...";
                            getch();
                            system("cls");
                        }

                        else if (choice4 == 5) // Display all books
                        {
                            Time.displayBooks();
                            Delay(2);
                            cout << "Press any key to continue...";
                            getch();
                            system("cls");
                        }

                        else if (choice4 == 6) // Display all students
                        {
                            vector<Student *> students;
                            Time.readStudentFile(students);
                            int i = 1;
                            for (auto student : students)
                            {
                                cout << i << ". ";
                                cout << student->get_name() << "-" << student->get_student_id() << endl;
                                i++;
                            }
                            Delay(2);
                            cout << "Press any key to continue...";
                            getch();
                            system("cls");
                        }

                        else if (choice4 == 7)
                        {
                            vector<Student *> _stu = Time.getStudents();
                            for (auto student : _stu)
                            {
                                cout << student->get_name() << "-"
                                     << student->get_student_id() << endl;
                            }
                            cout << "Press any key to continue..." << endl;
                            getch();
                            system("cls");
                        }
                    }
                }
                else
                {
                    cout << "Back to menu..." << endl;
                    Delay(2);
                    system("cls");
                }
            }
            else
            {
                cout << "Invalid choice!" << endl;
                Delay(2);
                system("cls");
            }
        }
    }
}

void StudentRegister(Library &Time)
{
    string userid, name, username, password, student_id, student_class, school;
    // Time.readStudentFile();
    // vector<Student *> students = Time.getStudents();

    cout << "Enter your user id: ";
    getline(cin, userid);
    // for (auto student : students)
    // {
    //     if (student->get_user_id() == userid)
    //     {
    //         cout << "This user id is already existed!" << endl;
    //         return;
    //     }
    // }

    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your username: ";
    getline(cin, username);
    cout << "Enter your password: ";
    getline(cin, password);
    cout << "Enter your student id: ";
    getline(cin, student_id);
    cout << "Enter your class: ";
    getline(cin, student_class);
    cout << "Enter your school: ";
    getline(cin, school);

    // cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // write to file
    fstream fout;
    fout.open("C:\\Users\\PC\\Desktop\\Final of final\\StudentAccount.csv", ios::out | ios::app);
    fout << userid << ","
         << name << ","
         << username << ","
         << password << ","
         << student_id << ","
         << student_class << ","
         << school << ","
         << "0;" << endl;
    fout.close();

    // add to vector
    Student *newstudent = new Student;
    newstudent->set_user_id(userid);
    newstudent->set_name(name);
    newstudent->set_username(username);
    newstudent->set_password(password);
    newstudent->set_student_id(student_id);
    newstudent->set_student_class(student_class);
    newstudent->set_school(school);
    Time.addStudent(newstudent);
    cout << "Register successfully!" << endl;
}

void LibrarianRegister(Library &Time)
{
    string userid, name, username, password, staff_id;
    cout << "Enter your user id: ";
    getline(cin, userid);
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your username: ";
    getline(cin, username);
    cout << "Enter your password: ";
    getline(cin, password);
    cout << "Enter your staff id: ";
    getline(cin, staff_id);

    fstream fout;
    fout.open("C:\\Users\\PC\\Desktop\\Final of final\\LibrarianAccount.csv", ios::out | ios::app);
    fout << userid << ","
         << name << ","
         << username << ","
         << password << ","
         << staff_id << endl;
    fout.close();

    Librarian *newlibrarian = new Librarian;
    newlibrarian->set_user_id(userid);
    newlibrarian->set_name(name);
    newlibrarian->set_username(username);
    newlibrarian->set_password(password);
    newlibrarian->set_staff_id(staff_id);
    Time.addLibrarian(newlibrarian);
}

void Delay(int second)
{
    time_t now = time(0);
    time_t later = now + second;
    while (now < later)
    {
        now = time(0);
    }
}