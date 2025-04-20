#include <iostream>
#include <string>
using namespace std;

// Abstract Class: Student
class Student {
public:
    virtual double getTuition(const string& status, int creditHours) const = 0;  // Pure Virtual Function
    virtual ~Student() {}  // Virtual destructor for safety
};

// Derived Class: GraduateStudent
class GraduateStudent : public Student {
private:
    string researchTopic;

public:
    void setResearchTopic(const string& topic) {
        researchTopic = topic;
    }

    string getResearchTopic() const {
        return researchTopic;
    }

    double getTuition(const string& status, int creditHours) const override {
        double rate = 0.0;

        if (status == "undergraduate") {
            rate = 200.0;
        } else if (status == "graduate") {
            rate = 300.0;
        } else if (status == "doctoral") {
            rate = 400.0;
        } else {
            cout << "Invalid student status!" << endl;
            return 0.0;
        }

        return rate * creditHours;
    }
};

int main() {
    GraduateStudent student;

    string topic, status;
    int credits;

    cout << "Enter Research Topic: ";
    getline(cin, topic);
    student.setResearchTopic(topic);

    cout << "Research Topic set to: " << student.getResearchTopic() << endl;

    cout << "Enter Student Status (undergraduate / graduate / doctoral): ";
    cin >> status;

    cout << "Enter Number of Credit Hours: ";
    cin >> credits;

    double tuition = student.getTuition(status, credits);

    if (tuition > 0.0) {
        cout << "Total Tuition Fee: $" << tuition << endl;
    }

    return 0;
}
