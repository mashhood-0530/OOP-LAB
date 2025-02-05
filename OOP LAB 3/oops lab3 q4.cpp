#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    string firstName;
    string lastName;
    double monthlySalary;

public:
    Employee(string fName, string lName, double salary) {
        firstName = fName;
        lastName = lName;
        monthlySalary = (salary > 0) ? salary : 0.0;
    }

    double getYearlySalary() {
        return monthlySalary * 12;
    }

    void giveRaise(double percentage) {
        monthlySalary += monthlySalary * (percentage / 100);
    }

    void display() {
        cout << "Employee: " << firstName << " " << lastName << " - Yearly Salary: " << getYearlySalary() << endl;
    }
};

int main() {
    Employee emp1("Mashhood", "Riaz", 3000.0);
    Employee emp2("Dawood", "Khan", 4000.0);

    cout << "Initial Salaries:" << endl;
    emp1.display();
    emp2.display();

    emp1.giveRaise(10);
    emp2.giveRaise(10);

    cout << "\nSalaries after 10% raise:" << endl;
    emp1.display();
    emp2.display();

    return 0;
}
