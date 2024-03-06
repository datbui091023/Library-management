#include "Library.h"
#include "Book.h"
#include "User.h"

void Library::addBook(Book *newbook)
{
    books.push_back(newbook);
    fstream fout;
    fout.open("C:\\Users\\PC\\Desktop\\Final of final\\Book.csv", ios::out | ios::app);
    fout << newbook->get_book_id() << "," << newbook->get_title() << "," << newbook->get_author() << ","
         << newbook->get_genre() << "," << newbook->get_isbn() << "," << newbook->get_quantity() << endl;
    cout << "Book added successfully!" << endl;
}

void Library::removeBook(string _id)
{
    auto it = books.begin();
    while (it != books.end())
    {
        auto book = *it;
        if (book->get_book_id() == _id)
        {
            books.erase(it);
            cout << "Book removed successfully!" << endl;
            return;
        }
        else
            it++;
    }
    cout << "Book not found!" << endl;
}

void Library::addStudent(Student *newstudent)
{
    students.push_back(newstudent);
    cout << "Student added successfully!" << endl;
}

void Library::removeStudent(string &student_id)
{
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i]->get_student_id() == student_id)
        {
            students.erase(students.begin() + i);
            cout << "Student removed successfully!" << endl;
        }
    }
    cout << "After remove: " << endl;
    for (auto student : students)
    {
        cout << student->get_student_id() << "-" << student->get_name()<< endl;
    }
    //cout << "Student not found!" << endl;
}

void Library::addLibrarian(Librarian *newlibrarian)
{
    librarians.push_back(newlibrarian);
    cout << "Librarian added successfully!" << endl;
}

void Library::removeLibrarian(string &librarian_id)
{
    auto it = librarians.begin();
    while (it != librarians.end())
    {
        auto librarian = *it;
        if (librarian->get_staff_id() == librarian_id)
        {
            librarians.erase(it);
            cout << "Librarian removed successfully!" << endl;
            return;
        }
    }
    cout << "Librarian not found!" << endl;
}

vector<Student *> Library::getStudents()
{
    return students;
}

vector<Librarian *> Library::getLibrarians()
{
    return librarians;
}

void Library::setStudents(vector<Student *> _students)
{
    this->students = _students;
}

void Library::setLibrarians(vector<Librarian *> librarians)
{
    this->librarians = librarians;
}

void Library::displayBooks()
{
    // Print table header
    cout << left << setw(10) << "Book ID" << setw(30) << "Title" << setw(20) << "Author"
         << setw(20) << "Genre" << setw(15) << "ISBN" << setw(10) << "Quantity"
         << "Status" << endl;

    // Print each book's information in a table-like format
    for (auto book : books)
    {
        cout << left << setw(10) << book->get_book_id() << setw(30) << book->get_title()
             << setw(20) << book->get_author();

        // Print genres
        cout << setw(20);
        for (auto genre : book->get_genre())
        {
            cout << genre << " ";
        }

        cout << setw(15) << book->get_isbn() << setw(10) << book->get_quantity()
             << book->getStatus() << endl;
    }
}

void Library::updateStudent(vector<Student *> &_students)
{
    fstream fout;
    fout.open("C:\\Users\\PC\\Desktop\\Final of final\\StudentAccount.csv", ios::out|ios::trunc);

    for ( auto &student : _students)
    {
        fout << student->get_user_id() << ","
             << student->get_name() << ","
             << student->get_username() << ","
             << student->get_password() << ","
             << student->get_student_id() << ","
             << student->get_student_class() << ","
             << student->get_school() << ","
             << student->get_borrowed_books() << endl;
    }

    fout.close();
}

void Library::updateBook()
{
    fstream fout;
    fout.open("C:\\Users\\PC\\Desktop\\Final of final\\Book.csv", ios::out);

    if (!fout.is_open())
    {
        cout << "Cannot open file!" << endl;
        return;
    }

    for (auto book : books)
    {
        fout << book->get_book_id() << "," << book->get_title() << "," << book->get_author() << ",";

        for (auto genre : book->get_genre())
        {
            fout << genre << ";";
        }

        fout << "," << book->get_isbn() << "," << book->get_quantity() << endl;
    }

    fout.close();
}

void Library::updateLibrarian()
{
    fstream fout;
    fout.open("C:\\Users\\PC\\Desktop\\Final of final\\LibrarianAccount.csv", ios::out | ios::app);

    if (!fout.is_open())
    {
        cout << "Cannot open file!" << endl;
        return;
    }

    for (auto librarian : librarians)
    {
        fout << librarian->get_user_id() << ","
             << librarian->get_name() << ","
             << librarian->get_username() << ","
             << librarian->get_password() << ","
             << librarian->get_staff_id() << endl;
    }

    fout.close();
}

void Library::readStudentFile(vector<Student *> &_students)
{
    // students.clear();
    fstream file;
    file.open("C:\\Users\\PC\\Desktop\\Final of final\\StudentAccount.csv", ios::in);

    if (!file.is_open())
    {
        cout << "Cannot open file!" << endl;
        return;
    }

    string _userid, _name, _username, _password, _studentid, _studentclass, _school, book_borrowed;
    while (file.peek() != EOF)
    {
        getline(file, _userid, ',');
        if (_userid == "")
            file.ignore();
        getline(file, _name, ',');
        getline(file, _username, ',');
        getline(file, _password, ',');
        getline(file, _studentid, ',');
        getline(file, _studentclass, ',');
        getline(file, _school, ',');
        getline(file, book_borrowed, '\n');

        Student *student = new Student;

        student->set_user_id(_userid);
        student->set_name(_name);
        student->set_username(_username);
        student->set_password(_password);
        student->set_student_id(_studentid);
        student->set_student_class(_studentclass);
        student->set_school(_school);

        _students.push_back(student); // Write to vector
    }
    setStudents(_students); // set to vector students in library
    file.close();
}

void Library::readBookFile()
{
    books.clear();
    fstream file;
    file.open("C:\\Users\\PC\\Desktop\\Final of final\\Book.csv", ios::in);

    if (!file.is_open())
    {
        cout << "Cannot open file!" << endl;
        return;
    }

    string _bookid, _title, _author, _genre, _isbn, _quantity;
    int __quantity;
    while (file.peek() != EOF)
    {
        getline(file >> ws, _bookid, ',');
        getline(file >> ws, _title, ',');
        getline(file >> ws, _author, ',');
        getline(file >> ws, _genre, ',');
        getline(file >> ws, _isbn, ',');
        getline(file >> ws, _quantity, '\n');

        __quantity = stoi(_quantity);

        Book *book = new Book;

        book->set_book_id(_bookid);
        book->set_title(_title);
        book->set_author(_author);
        book->set_genre(_genre);
        book->set_isbn(_isbn);
        book->set_quantity(__quantity);

        books.push_back(book);
    }
    file.close();
}

Book *Library::findBookById(string _id)
{
    for (auto book : books)
    {
        if (book->get_book_id() == _id)
        {
            return book;
        }
    }
    return nullptr;
}

Student *Library::findStudentById(string _id)
{
    for (auto student : students)
    {
        if (student->get_student_id() == _id)
        {
            return student;
        }
    }
    return nullptr;
}

void Library::readLibrarianFile(vector<Librarian *> &librarians)
{
    fstream file;
    file.open("C:\\Users\\PC\\Desktop\\Final of final\\LibrarianAccount.csv", ios::in);

    if (!file.is_open())
    {
        cout << "Cannot open file!" << endl;
        return;
    }

    string _userid, _name, _username, _password, _staffid;
    while (file.peek() != EOF)
    {
        getline(file, _userid, ',');
        getline(file, _name, ',');
        getline(file, _username, ',');
        getline(file, _password, ',');
        getline(file, _staffid, '\n');

        Librarian *librarian = new Librarian;

        librarian->set_user_id(_userid);
        librarian->set_name(_name);
        librarian->set_username(_username);
        librarian->set_password(_password);
        librarian->set_staff_id(_staffid);

        librarians.push_back(librarian);
    }
    setLibrarians(librarians);
    file.close();
}

void Library::StudentLogin(Student *&_student)
{
    string usr, pass;
    cout << "Enter your username: ";
    getline(cin, usr);
    cout << "Enter your password: ";
    getline(cin, pass);

    // cout << "Checking..." << endl;
    // cout << "'" << usr << "'" << ";" << "'" << pass << "'" << endl;

    for (auto student : students)
    {
        cout << "Checking..." << endl;
        // cout << student->get_username() << endl;
        // cout << student->get_password() << endl;
        if (pass == student->get_password() && usr == student->get_username())
        {
            cout << "Login successfully!" << endl;
            _student = student;
            return;
        }
    }

    cout << "Login failed!" << endl;
}

void Library::LibrarianLogin(Librarian *&_librarian)
{
    string usr, pass;
    cout << "Enter your username: ";
    getline(cin, usr);
    cout << "Enter your password: ";
    getline(cin, pass);

    // cout << "Checking..." << endl;
    // cout << "'" << usr << "'" << ";" << "'" << pass << "'" << endl;

    for (auto librarian : librarians)
    {
        cout << "Checking..." << endl;
        // cout << librarian->get_username() << endl;
        // cout << librarian->get_password() << endl;
        if (pass == librarian->get_password() && usr == librarian->get_username())
        {
            cout << "Login successfully!" << endl;
            _librarian = librarian;
            return;
        }
    }

    cout << "Login failed!" << endl;
}
