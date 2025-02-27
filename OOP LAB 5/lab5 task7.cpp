#include <iostream>

using namespace std;

class Student {
private:
    const int roll_no;  // Constant variable (must be initialized)

public:
    // Constructor to initialize the const variable at runtime
    Student(int roll) : roll_no(roll) {}

    // Function to display student details
    void display() const {
        cout << "Student Roll Number: " << roll_no << endl;
    }
};

int main() {
    int roll;
    cout << "Enter student roll number: ";
    cin >> roll;

    // Creating Student object with user input
    Student student(roll);

    // Display student details
    student.display();

    return 0;
}
