#include <iostream>
#include <vector>
using namespace std;

class Media {
protected:
    string title, publicationDate, uniqueID, publisher;

public:
    Media(string t, string pDate, string uID, string pub)
        : title(t), publicationDate(pDate), uniqueID(uID), publisher(pub) {}

    virtual void displayInfo() const {
        cout << "Title: " << title << "\nPublication Date: " << publicationDate
             << "\nUnique ID: " << uniqueID << "\nPublisher: " << publisher << endl;
    }

    string getTitle() const { return title; }
    string getPublicationDate() const { return publicationDate; }

    virtual ~Media() {}
};

class Book : public Media {
private:
    string author, ISBN;
    int numberOfPages;

public:
    Book(string t, string pDate, string uID, string pub, string a, string isbn, int pages)
        : Media(t, pDate, uID, pub), author(a), ISBN(isbn), numberOfPages(pages) {}

    void displayInfo() const override {
        Media::displayInfo();
        cout << "Author: " << author << "\nISBN: " << ISBN << "\nPages: " << numberOfPages << endl;
    }

    string getAuthor() const { return author; }
};

class DVD : public Media {
private:
    string director;
    int duration;
    float rating;

public:
    DVD(string t, string pDate, string uID, string pub, string d, int dur, float r)
        : Media(t, pDate, uID, pub), director(d), duration(dur), rating(r) {}

    void displayInfo() const override {
        Media::displayInfo();
        cout << "Director: " << director << "\nDuration: " << duration << " min\nRating: " << rating << endl;
    }
};

class CD : public Media {
private:
    string artist, genre;
    int numberOfTracks;

public:
    CD(string t, string pDate, string uID, string pub, string art, string g, int tracks)
        : Media(t, pDate, uID, pub), artist(art), genre(g), numberOfTracks(tracks) {}

    void displayInfo() const override {
        Media::displayInfo();
        cout << "Artist: " << artist << "\nGenre: " << genre << "\nTracks: " << numberOfTracks << endl;
    }
};

void searchMedia(const vector<Media*>& library, string title) {
    for (auto m : library) {
        if (m->getTitle() == title) {
            cout << "Found:\n";
            m->displayInfo();
            return;
        }
    }
    cout << "Media not found.\n";
}

void searchMedia(const vector<Media*>& library, string author, bool isAuthor) {
    for (auto m : library) {
        Book* book = dynamic_cast<Book*>(m);
        if (book && book->getAuthor() == author) {
            cout << "Found:\n";
            book->displayInfo();
            return;
        }
    }
    cout << "Book not found.\n";
}

void searchMedia(const vector<Media*>& library, int year) {
    for (auto m : library) {
        if (stoi(m->getPublicationDate()) == year) {
            cout << "Found:\n";
            m->displayInfo();
            return;
        }
    }
    cout << "No media found from year " << year << ".\n";
}

int main() {
    vector<Media*> library;

    library.push_back(new Book("The Great Gatsby", "1925", "B001", "Scribner", "F. Scott Fitzgerald", "1234567890", 180));
    library.push_back(new DVD("Inception", "2010", "D001", "Warner Bros", "Christopher Nolan", 148, 8.8));
    library.push_back(new CD("Thriller", "1982", "C001", "Epic", "Michael Jackson", "Pop", 9));

    cout << "Library Collection:\n";
    for (auto m : library) {
        m->displayInfo();
        cout << "-----------------\n";
    }

    cout << "\nSearching by Title:\n";
    searchMedia(library, "Inception");

    cout << "\nSearching by Author:\n";
    searchMedia(library, "F. Scott Fitzgerald", true);

    cout << "\nSearching by Year:\n";
    searchMedia(library, 1982);

    for (auto m : library) delete m;

    return 0;
}
