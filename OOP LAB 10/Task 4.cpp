#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>  // for rename()
using namespace std;

class Logger {
private:
    string base_filename;
    size_t max_size;
    int file_index;
    ofstream current_file;

    size_t getFileSize(const string& filename) {
        ifstream in(filename.c_str(), ios::binary | ios::ate);
        if (!in.is_open()) {
            return 0;
        }
        return in.tellg();
    }

    void rotate() {
        current_file.close();
        string old_name = base_filename + ".txt";
        string new_name = base_filename + to_string(file_index++) + ".txt";
        if (rename(old_name.c_str(), new_name.c_str()) != 0) {
            cerr << "Error renaming file!\n";
            exit(1);
        }
        current_file.open(base_filename + ".txt", ios::out | ios::app);
    }

public:
    Logger(const string& filename, size_t maxSizeBytes)
        : base_filename(filename), max_size(maxSizeBytes), file_index(1) {
        current_file.open(base_filename + ".txt", ios::out | ios::app);
        if (!current_file.is_open()) {
            cerr << "Failed to open log file.\n";
            exit(1);
        }
    }

    ~Logger() {
        if (current_file.is_open()) {
            current_file.close();
        }
    }

    void log(const string& message) {
        current_file << message << endl;
        current_file.flush();

        if (getFileSize(base_filename + ".txt") >= max_size) {
            rotate();
        }
    }
};

int main() {
    Logger logger("log", 1024 * 1024); // 1MB max

    // Dummy logging
    for (int i = 0; i < 100000; ++i) {
        logger.log("This is log message number: " + to_string(i));
    }

    cout << "Logging complete.\n";
    return 0;
}
