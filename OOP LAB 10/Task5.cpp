#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // for exit()
using namespace std;

const string FILENAME = "todo.txt";

void addTask() {
    string task;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, task);

    ofstream file(FILENAME.c_str(), ios::app);
    if (!file) {
        cerr << "Cannot open file for writing.\n";
        exit(1);
    }
    file << "[ ] " << task << endl;
    file.close();
    cout << "Task added.\n";
}

void viewTasks() {
    ifstream file(FILENAME.c_str());
    if (!file) {
        cerr << "Cannot open file for reading.\n";
        exit(1);
    }

    string line;
    int index = 1;
    while (getline(file, line)) {
        cout << index++ << ". " << line << endl;
    }
    file.close();
}

void markTaskDone() {
    ifstream file(FILENAME.c_str());
    if (!file) {
        cerr << "Cannot open file for reading.\n";
        exit(1);
    }

    const int MAX = 100;
    string tasks[MAX];
    int count = 0;

    while (getline(file, tasks[count]) && count < MAX) {
        count++;
    }
    file.close();

    viewTasks();
    int taskNo;
    cout << "Enter task number to mark as done: ";
    cin >> taskNo;

    if (taskNo < 1 || taskNo > count) {
        cerr << "Invalid task number.\n";
        return;
    }

    if (tasks[taskNo - 1].substr(0, 3) == "[ ]") {
        tasks[taskNo - 1].replace(0, 3, "[X]");
    }

    ofstream out(FILENAME.c_str());
    if (!out) {
        cerr << "Cannot open file for writing.\n";
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        out << tasks[i] << endl;
    }
    out.close();

    cout << "Task marked as done.\n";
}

int main() {
    int choice;
    while (true) {
        cout << "\n--- To-Do List Menu ---\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Done\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: markTaskDone(); break;
            case 4: cout << "Exiting.\n"; return 0;
            default: cout << "Invalid choice.\n"; break;
        }
    }
}
