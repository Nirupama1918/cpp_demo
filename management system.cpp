#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

// Book Class - Urvi's Task
class Book {
    int id;
    string title, author;
    bool isIssued;

public:
    Book(int bookId, string bookTitle, string bookAuthor)
        : id(bookId), title(bookTitle), author(bookAuthor), isIssued(false) {}

    void display() const {
        cout << setw(10) << id << setw(30) << title << setw(20) << author << setw(15)
             << (isIssued ? "Issued" : "Available") << endl;
    }

    int getId() const { return id; }
    string getTitle() const { return title; }
    bool getStatus() const { return isIssued; }
    void issue() { isIssued = true; }
    void returnBook() { isIssued = false; }
};

// User Class - Nidhi's Task
class User {
    string name;
    int userId;
    vector<int> issuedBooks;

public:
    User(int id, string userName) : userId(id), name(userName) {}

    void display() const {
        cout << "User ID: " << userId << ", Name: " << name << endl;
        cout << "Books Issued: ";
        if (issuedBooks.empty())
            cout << "None";
        else
            for (int bookId : issuedBooks)
                cout << bookId << " ";
        cout << endl;
    }

    int getId() const { return userId; }
    string getName() const { return name; }
    void issueBook(int bookId) { issuedBooks.push_back(bookId); }
    void returnBook(int bookId) {
        issuedBooks.erase(remove(issuedBooks.begin(), issuedBooks.end(), bookId), issuedBooks.end());
    }
};

// Library Class - Harshita's Task
class Library {
    vector<Book> books;
    vector<User> users;

    // File Handling - Rajkumari's Task
    void saveBooksToFile() {
        ofstream file("books.txt");
        for (const auto& book : books) {
            file << book.getId() << "|" << book.getTitle() << "|"
                 << book.getStatus() << endl;
        }
        file.close();
    }

    void loadBooksFromFile() {
        ifstream file("books.txt");
        int id;
        string title, status;
        while (file >> id) {
            file.ignore(); // ignore the delimiter
            getline(file, title, '|');
            getline(file, status);
            books.emplace_back(id, title, "Unknown Author");
            if (status == "1") books.back().issue();
        }
        file.close();
    }

public:
    Library() {
        loadBooksFromFile();
        // Manually adding some users
        users.push_back(User(101, "John Doe"));
        users.push_back(User(102, "Jane Smith"));
    }

    void addBook() {
        int id;
        string title, author;

        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Book Author: ";
        getline(cin, author);

        books.emplace_back(id, title, author);
        saveBooksToFile();
        cout << "Book added successfully!" << endl;
    }

    void displayBooks() const {
        if (books.empty()) {
            cout << "No books available in the library." << endl;
            return;
        }

        cout << setw(10) << "Book ID" << setw(30) << "Title" << setw(20) << "Author"
             << setw(15) << "Status" << endl;
        cout << string(75, '-') << endl;

        for (const auto& book : books) {
            book.display();
        }
    }

    void issueBook() {
        int bookId, userId;
        cout << "Enter User ID: ";
        cin >> userId;

        // Check if User ID exists
        bool userExists = false;
        for (const auto& user : users) {
            if (user.getId() == userId) {
                userExists = true;
                break;
            }
        }

        if (!userExists) {
            cout << "Error: User ID not found!" << endl;
            return;
        }

        cout << "Enter Book ID to issue: ";
        cin >> bookId;

        // Check if Book ID exists and issue the book
        bool bookFound = false;
        for (auto& book : books) {
            if (book.getId() == bookId) {
                bookFound = true;
                if (book.getStatus()) {
                    cout << "Error: Book is already issued!" << endl;
                    return;
                } else {
                    book.issue();
                    for (auto& user : users) {
                        if (user.getId() == userId) {
                            user.issueBook(bookId);
                            break;
                        }
                    }
                    cout << "Book issued successfully!" << endl;
                    saveBooksToFile();
                    return;
                }
            }
        }

        if (!bookFound) {
            cout << "Error: Book ID not found!" << endl;
        }
    }

    void returnBook() {
        int bookId, userId;
        cout << "Enter User ID: ";
        cin >> userId;

        // Check if User ID exists
        bool userExists = false;
        for (const auto& user : users) {
            if (user.getId() == userId) {
                userExists = true;
                break;
            }
        }

        if (!userExists) {
            cout << "Error: User ID not found!" << endl;
            return;
        }

        cout << "Enter Book ID to return: ";
        cin >> bookId;

        // Check if Book ID exists and return the book
        bool bookFound = false;
        for (auto& book : books) {
            if (book.getId() == bookId) {
                bookFound = true;
                if (book.getStatus()) {
                    book.returnBook();
                    for (auto& user : users) {
                        if (user.getId() == userId) {
                            user.returnBook(bookId);
                            break;
                        }
                    }
                    cout << "Book returned successfully!" << endl;
                    saveBooksToFile();
                    return;
                } else {
                    cout << "Error: This book was not issued!" << endl;
                    return;
                }
            }
        }

        if (!bookFound) {
            cout << "Error: Book ID not found!" << endl;
        }
    }
};

int main() {
    Library library;
    int choice;

    do {
        cout << "\n=== LIBRARY MANAGEMENT SYSTEM ===\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                library.addBook();
                break;
            case 2:
                library.displayBooks();
                break;
            case 3:
                library.issueBook();
                break;
            case 4:
                library.returnBook();
                break;
            case 5:
                cout << "Exiting the system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}