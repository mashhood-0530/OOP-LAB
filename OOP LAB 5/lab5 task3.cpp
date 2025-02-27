#include <iostream>
#include <string>

// Book class
class Book {
public:
    Book(const std::string& isbn, const std::string& title, const std::string& author)
        : isbn(isbn), title(title), author(author) {}

    std::string getISBN() const { return isbn; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }

private:
    std::string isbn;
    std::string title;
    std::string author;
};

// Catalog class
class Catalog {
public:
    Catalog() : bookCount(0) {}

    void addBook(const std::string& isbn, const std::string& location) {
        if (bookCount < MAX_BOOKS) {
            isbns[bookCount] = isbn;
            locations[bookCount] = location;
            bookCount++;
        } else {
            std::cout << "Catalog is full. Cannot add more books.\n";
        }
    }

    void removeBook(const std::string& isbn) {
        for (int i = 0; i < bookCount; ++i) {
            if (isbns[i] == isbn) {
                // Shift remaining elements to the left
                for (int j = i; j < bookCount - 1; ++j) {
                    isbns[j] = isbns[j + 1];
                    locations[j] = locations[j + 1];
                }
                bookCount--;
                std::cout << "Book with ISBN " << isbn << " removed from catalog.\n";
                return;
            }
        }
        std::cout << "Book with ISBN " << isbn << " not found in catalog.\n";
    }

    std::string findBookLocation(const std::string& isbn) const {
        for (int i = 0; i < bookCount; ++i) {
            if (isbns[i] == isbn) {
                return locations[i];
            }
        }
        return "Book not found in catalog.";
    }

private:
    static const int MAX_BOOKS = 100; // Maximum number of books in the catalog
    std::string isbns[MAX_BOOKS];
    std::string locations[MAX_BOOKS];
    int bookCount;
};

// Library class
class Library {
public:
    Library(const std::string& name, const std::string& address)
        : name(name), address(address), bookCount(0) {}

    void addBook(Book* book, const std::string& location) {
        if (bookCount < MAX_BOOKS) {
            books[bookCount] = book;
            catalog.addBook(book->getISBN(), location);
            bookCount++;
        } else {
            std::cout << "Library is full. Cannot add more books.\n";
        }
    }

    void removeBook(const std::string& isbn) {
        for (int i = 0; i < bookCount; ++i) {
            if (books[i]->getISBN() == isbn) {
                // Shift remaining elements to the left
                for (int j = i; j < bookCount - 1; ++j) {
                    books[j] = books[j + 1];
                }
                bookCount--;
                catalog.removeBook(isbn);
                std::cout << "Book with ISBN " << isbn << " removed from library.\n";
                return;
            }
        }
        std::cout << "Book with ISBN " << isbn << " not found in library.\n";
    }

    std::string findBookInCatalog(const std::string& isbn) const {
        return catalog.findBookLocation(isbn);
    }

    void printLibraryInfo() const {
        std::cout << "Library Name: " << name << "\n";
        std::cout << "Address: " << address << "\n";
        std::cout << "Number of Books: " << bookCount << "\n";
    }

private:
    static const int MAX_BOOKS = 100; // Maximum number of books in the library
    std::string name;
    std::string address;
    Catalog catalog; // Composition
    Book* books[MAX_BOOKS]; // Aggregation (using raw pointers)
    int bookCount;
};

// Main function
int main() {
    // Create a Library object
    Library library("Central Library", "123 Library St");

    // Create some Book objects
    Book book1("978-3-16-148410-0", "The Great Gatsby", "F. Scott Fitzgerald");
    Book book2("978-0-7432-7356-5", "To Kill a Mockingbird", "Harper Lee");

    // Add books to the library
    library.addBook(&book1, "Fiction Section, Shelf 1");
    library.addBook(&book2, "Fiction Section, Shelf 2");

    // Print library info
    library.printLibraryInfo();

    // Search for a book in the catalog
    std::cout << "Searching for ISBN 978-3-16-148410-0: "
              << library.findBookInCatalog("978-3-16-148410-0") << "\n";

    std::cout << "Searching for ISBN 978-0-7432-7356-5: "
              << library.findBookInCatalog("978-0-7432-7356-5") << "\n";

    // Remove a book and search again
    library.removeBook("978-3-16-148410-0");
    std::cout << "After removal, searching for ISBN 978-3-16-148410-0: "
              << library.findBookInCatalog("978-3-16-148410-0") << "\n";

    return 0;
}