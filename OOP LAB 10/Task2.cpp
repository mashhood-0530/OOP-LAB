#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct Employee {
    int id;
    string name;
    string designation;
    int years_of_service;
};

vector<Employee> readEmployees(const string& filename) {
    vector<Employee> employees;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Employee emp;
        ss >> emp.id >> emp.name >> emp.designation >> emp.years_of_service;
        employees.push_back(emp);
    }
    file.close();
    return employees;
}

void writeEmployees(const string& filename, const vector<Employee>& employees) {
    ofstream file(filename, ios::trunc);
    for (const auto& emp : employees) {
        file << emp.id << " " << emp.name << " " << emp.designation << " " << emp.years_of_service << endl;
    }
    file.close();
}

void dummyData(const string& filename) {
    ofstream file(filename);
    file << "1 Alice Manager 3\n";
    file << "2 Bob Developer 1\n";
    file << "3 Charlie Manager 1\n";
    file << "4 David Tester 4\n";
    file << "5 Eve Manager 5\n";
    file.close();
}

int main() {
    string filename = "employees.txt";
    
    // Step 1: Write dummy data
    dummyData(filename);

    // Step 2: Read data
    vector<Employee> employees = readEmployees(filename);

    // Step 3: Find Managers with >= 2 years
    vector<Employee> filtered;
    for (const auto& emp : employees) {
        if (emp.designation == "Manager" && emp.years_of_service >= 2) {
            filtered.push_back(emp);
        }
    }

    // Step 4: Delete all data except filtered
    writeEmployees(filename, filtered);

    // Step 5: Increment ID and years of service
    for (auto& emp : filtered) {
        emp.id++;
        emp.years_of_service++;
    }
    writeEmployees(filename, filtered);

    cout << "CRUD operations completed.\n";
    return 0;
}
