#include <iostream>
#include <any>
#include <stdexcept>
#include <string>

using namespace std;

// Custom exception for type mismatch
class BadTypeException : public exception {
public:
    const char* what() const noexcept override {
        return "BadTypeException: Requested type does not match the stored type.";
    }
};

// Templated container class using std::any
class TypeSafeContainer {
private:
    std::any value;

public:
    // Store any type
    template <typename T>
    void store(const T& val) {
        value = val;
    }

    // Retrieve value with type safety
    template <typename T>
    T get() const {
        try {
            return std::any_cast<T>(value);
        } catch (const std::bad_any_cast&) {
            throw BadTypeException();
        }
    }
};
int main() {
    TypeSafeContainer container;

    try {
        container.store<int>(42);
        cout << "Stored int: " << container.get<int>() << endl;

        container.store<string>("Hello World");
        cout << "Stored string: " << container.get<string>() << endl;

        // This will throw BadTypeException
        cout << "Attempting to get int (wrong type): ";
        cout << container.get<int>() << endl;

    } catch (const BadTypeException& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}
