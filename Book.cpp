#include "Book.h"

string Book::get_book_id()
{
    return book_id;
}

string Book::get_title()
{
    return title;
}

string Book::get_author()
{
    return author;
}

string Book::get_genre()
{
    return genre;
}

string Book::get_isbn()
{
    return isbn;
}

int Book::get_quantity()
{
    return quantity;
}

int Book::get_available_copies()
{
    return available_copies;
}

string Book::getStatus()
{
    return currentStatus;
}

void Book::set_book_id(string book_id)
{
    this->book_id = book_id;
}

void Book::set_title(string title)
{
    this->title = title;
}

void Book::set_author(string author)
{
    this->author = author;
}

void Book::set_genre(string genre)
{
    this->genre = genre;
}

void Book::set_isbn(string isbn)
{
    this->isbn = isbn;
}

void Book::set_quantity(int quantity)
{
    this->quantity = quantity;
}

bool Book::isAvailable()
{
    return currentStatus == "Available" && quantity > 0;
}

void Book::borrow_books()
{
    if (isAvailable())
    {
        available_copies--;
        currentStatus = "Borrowed";
        borrowDate = time(0); // Set borrow date to current date
        dueDate = borrowDate + (30 * 4 * 60 * 60); // Set due date to 30 days from borrow date
        cout << "Book borrowed successfully" << endl;
    }
    else
    {
        cout << "Book is not available" << endl;
    }
}

void Book::return_book()
{
    available_copies++;
    currentStatus = "Available";
    returnDate = time(0); // Set return date to current date
    dueDate = 0;          // reset due date
    cout << "Book returned successfully" << endl;
}

double calculate_fine(Book &book)
{
    if (book.returnDate == 0)
    {
        return 0;
    }
    else
    {
        double fine = 0;
        time_t diff = book.returnDate - book.dueDate;
        if (diff > 0)
        {
            fine = (diff / (30 * 4 * 60 * 60)) * 30000;
        }
        return fine;
    }
}
