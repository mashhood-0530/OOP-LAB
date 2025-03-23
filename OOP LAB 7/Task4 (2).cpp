#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Course;

class Person {
protected:
    string name;
    int id;
    string address;
    string phone;
    string mail;

public:
    Person(string n, int i, string a, string p, string m)
        : name(n), id(i), address(a), phone(p), mail(m) {}

    virtual void display() {
        cout << "Name: " << name << "\nID: " << id
             << "\nAddress: " << address << "\nPhone: " << phone
             << "\nEmail: " << mail << endl;
    }

    string getName() { return name; }
    int getId() { return id; }
};

class Course {
    int courseId;
    string courseName;
    int credits;
    string instructor;
    string schedule;

public:
    Course(int id, string name, int cr, string ins, string sch)
        : courseId(id), courseName(name), credits(cr), instructor(ins), schedule(sch) {}

    void display() {
        cout << "Course ID: " << courseId << "\nCourse Name: " << courseName
             << "\nCredits: " << credits << "\nInstructor: " << instructor
             << "\nSchedule: " << schedule << endl;
    }

    string getCourseName() { return courseName; }
};

class Student : public Person {
    vector<Course> coursesEnrolled;
    double GPA;
    int enrollmentYear;

public:
    Student(string n, int i, string a, string p, string m, vector<Course> c, double g, int y)
        : Person(n, i, a, p, m), coursesEnrolled(c), GPA(g), enrollmentYear(y) {}

    void enrollCourse(Course c) {
        coursesEnrolled.push_back(c);
        cout << name << " enrolled in " << c.getCourseName() << endl;
    }

    void display() override {
        Person::display();
        cout << "GPA: " << GPA << "\nEnrollment Year: " << enrollmentYear << "\nCourses: ";
        for (auto &c : coursesEnrolled) cout << c.getCourseName() << " ";
        cout << endl;
    }
};

class Professor : public Person {
    string department;
    vector<Course> coursesTaught;
    double salary;

public:
    Professor(string n, int i, string a, string p, string m, string d, vector<Course> c, double s)
        : Person(n, i, a, p, m), department(d), coursesTaught(c), salary(s) {}

    void display() override {
        Person::display();
        cout << "Department: " << department << "\nSalary: " << salary << "\nCourses: ";
        for (auto &c : coursesTaught) cout << c.getCourseName() << " ";
        cout << endl;
    }
};

int main() {
    Course c1(101, "Mathematics", 3, "Dr. Smith", "MWF 10AM");
    Course c2(102, "Physics", 4, "Dr. Brown", "TTh 2PM");
    vector<Course> studentCourses = {c1, c2};
    Student s1("Ali Raza", 1001, "Karachi", "1234567890", "ali@example.com", studentCourses, 3.8, 2023);

    vector<Course> profCourses = {c1};
    Professor p1("Dr. John", 2001, "Lahore", "9876543210", "john@example.com", "Science", profCourses, 50000);

    s1.display();
    cout << "\n";
    p1.display();

    return 0;
}
