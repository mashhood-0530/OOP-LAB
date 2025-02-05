#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string bookName;
    string isbn;
    string author;
    string publisher;

public:
    Book(string bookName, string isbn, string author, string publisher) {
        this->bookName = bookName;
        this->isbn = isbn;
        this->author = author;
        this->publisher = publisher;
    }

    string getBookName() { return this->bookName; }
    string getISBN() { return this->isbn; }
    string getAuthor() { return this->author; }
    string getPublisher() { return this->publisher; }
    
    string getBookInfo() {
        return "Book Name: " + this->bookName + "\nISBN: " + this->isbn + "\nAuthor: " + this->author + "\nPublisher: " + this->publisher;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 21) {
        cout << "Usage: <book1_name> <book1_isbn> <book1_author> <book1_publisher> ... (for 5 books)" << endl;
        return 1;
    }
    
    Book* books[5];
    for (int i = 0; i < 5; i++) {
        books[i] = new Book(argv[i * 4 + 1], argv[i * 4 + 2], argv[i * 4 + 3], argv[i * 4 + 4]);
    }
    
    for (int i = 0; i < 5; i++) {
        cout << "Book " << i + 1 << " Information:\n" << books[i]->getBookInfo() << "\n" << endl;
        delete books[i];
    }
    
    return 0;
}
