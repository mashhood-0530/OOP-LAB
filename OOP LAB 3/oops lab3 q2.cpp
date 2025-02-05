#include <iostream>
using namespace std;

class Date {
public:
    int month;
    int day;
    int year;

    Date(int m, int d, int y) : month(m), day(d), year(y) {}

    void displayDate() {
        cout << month << "/" << day << "/" << year << endl;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: ./program month day year" << endl;
        return 1;
    }

    int month = stoi(argv[1]);
    int day = stoi(argv[2]);
    int year = stoi(argv[3]);

    Date date(month, day, year);
    date.displayDate();

    return 0;
}
