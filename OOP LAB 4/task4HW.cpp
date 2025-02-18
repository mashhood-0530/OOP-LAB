#include <iostream>
#include <string>
using namespace std;

class Books
{
    string author, title, publisher;
    int stock;
    double price;

public:
    Books(string auth, string t, string pub, double p, int s)
        : author(auth), title(t), publisher(pub), price(p), stock(s) {}

string GetTitle()
{
    return title;
}
string GetAuthor()
{
    return author;
}
bool search_a_book(string t, string a)
    {
        if (title == t && author == a)
        {
            cout << "Title: " << title << endl;
            cout << "Author: " << author << endl;
            cout << "Publisher: " << publisher << endl;
            cout << "Stock: " << stock << endl;
            cout << "Price: " << price << endl;

            if (stock > 0)
            {
                int qty;
                cout << "How many copies do you want?: ";
                cin >> qty;

                if (qty <= stock)
                {
                    cout << "Total price: " << qty * price << endl;
                    stock -= qty;
                    return true;
                }
                else
                {
                    cout << "Not enough stock available!" << endl;
                    return false;
                }
            }
            else
            {
                cout << "Book is out of stock!" << endl;
                return false;
            }
        }
    }
};

int main()
{
    Books books[5] = {
        {"J.K. Rowling", "Harry Potter and the Sorcerer's Stone", "Bloomsbury", 39.99, 15},
        {"George Orwell", "1984", "Secker & Warburg", 14.99, 10},
        {"J.R.R. Tolkien", "The Lord of the Rings", "Allen & Unwin", 29.99, 12},
        {"F. Scott Fitzgerald", "The Great Gatsby", "Scribner", 10.99, 8},
        {"Harper Lee", "To Kill a Mockingbird", "J.B. Lippincott & Co.", 12.99, 20}};

        string t, a;
        cout << "\nEnter book title: ";
        getline(cin, t);
        cout << "Enter author name: ";
        getline(cin, a);

        bool found = false;
        for (int i = 0; i < 5; i++)
        {
            found=books[i].search_a_book(t, a);
            if(found==true)
            break;
        }
        if (!found)
        {
            cout << "Book not found!" << endl;
        }
        return 0;
}