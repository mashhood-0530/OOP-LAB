#include <iostream>
#include <string>
using namespace std;

// Base class
class Person {
protected:
    string name;
    int id;
    double salary;

public:
    virtual void getdata() {
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Salary: ";
        cin >> salary;
    }

    virtual void displaydata() const {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Salary: Rs. " << salary << endl;
    }

    virtual void bonus() const {
        cout << "Generic bonus (Person class): Rs. " << (salary * 0.05) << endl;
    }

    virtual ~Person() {}
};

// Derived class Admin
class Admin : virtual public Person {
public:
    void getdata() override {
        cout << "Enter Admin Details:" << endl;
        Person::getdata();
    }

    void displaydata() const override {
        cout << "Admin Details:" << endl;
        Person::displaydata();
    }

    void bonus() const override {
        cout << "Admin bonus: Rs. " << (salary * 0.10) << endl;
    }
};

// Derived class Account
class Account : virtual public Person {
public:
    void getdata() override {
        cout << "Enter Account Staff Details:" << endl;
        Person::getdata();
    }

    void displaydata() const override {
        cout << "Account Staff Details:" << endl;
        Person::displaydata();
    }

    void bonus() const override {
        cout << "Account Staff bonus: Rs. " << (salary * 0.12) << endl;
    }
};

// Derived class Master (inherits Admin and Account)
class Master : public Admin, public Account {
public:
    void getdata() override {
        cout << "Enter Master Employee Details:" << endl;
        Person::getdata();  // Only one Person copy because of virtual inheritance
    }

    void displaydata() const override {
        cout << "Master Employee Details:" << endl;
        Person::displaydata();
    }

    void bonus() const override {
        cout << "Master Employee bonus: Rs. " << (salary * 0.20) << endl;
    }
};

int main() {
    Person *ptr;

    Admin adminEmp;
    Account accountEmp;
    Master masterEmp;

    cout << "\n--- Admin Employee ---" << endl;
    ptr = &adminEmp;
    ptr->getdata();
    ptr->displaydata();
    ptr->bonus();

    cout << "\n--- Account Staff ---" << endl;
    ptr = &accountEmp;
    ptr->getdata();
    ptr->displaydata();
    ptr->bonus();

    cout << "\n--- Master Employee ---" << endl;
    ptr = &masterEmp;
    ptr->getdata();
    ptr->displaydata();
    ptr->bonus();

    return 0;
}
