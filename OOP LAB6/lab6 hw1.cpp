#include <iostream>
#include <string>

// Base class for Books
class Books {
protected:
    std::string genre;

public:
    Books(const std::string& bookGenre)
        : genre(bookGenre) {}

    virtual ~Books() = default;

    virtual void displayDetails() const {
        std::cout << "Genre: " << genre << std::endl;
    }
};

// Derived class for Novels
class Novel : public Books {
private:
    std::string title;
    std::string author;

public:
    Novel(const std::string& bookTitle, const std::string& bookAuthor)
        : Books("Novel"), title(bookTitle), author(bookAuthor) {}

    void displayDetails() const override {
        Books::displayDetails();
        std::cout << "Title: " << title << std::endl;
        std::cout << "Author: " << author << std::endl;
    }
};

// Derived class for Mystery
class Mystery : public Books {
private:
    std::string title;
    std::string author;

public:
    Mystery(const std::string& bookTitle, const std::string& bookAuthor)
        : Books("Mystery"), title(bookTitle), author(bookAuthor) {}

    void displayDetails() const override {
        Books::displayDetails();
        std::cout << "Title: " << title << std::endl;
        std::cout << "Author: " << author << std::endl;
    }
};

int main() {
    // Create objects of different book genres
    Novel novel("To Kill a Mockingbird", "Harper Lee");
    Mystery mystery("The Girl with the Dragon Tattoo", "Stieg Larsson");

    // Display details of each book
    std::cout << "Novel Details:" << std::endl;
    novel.displayDetails();
    std::cout << "-------------------" << std::endl;

    std::cout << "Mystery Details:" << std::endl;
    mystery.displayDetails();
    std::cout << "-------------------" << std::endl;

    return 0;
}