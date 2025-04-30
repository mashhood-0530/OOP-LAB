#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// Custom exception for underflow
class StackUnderflowException : public exception {
public:
    const char* what() const noexcept override {
        return "StackUnderflowException: Stack is empty.";
    }
};

// Templated Stack class
template <typename T>
class Stack {
private:
    vector<T> data;

public:
    // Push element onto stack
    void push(const T& value) {
        data.push_back(value);
    }

    // Pop element from stack
    void pop() {
        if (data.empty()) {
            throw StackUnderflowException();
        }
        data.pop_back();
    }

    // Return top element
    T& top() {
        if (data.empty()) {
            throw StackUnderflowException();
        }
        return data.back();
    }

    // Check if stack is empty
    bool empty() const {
        return data.empty();
    }

    // Return size of stack
    size_t size() const {
        return data.size();
    }
};
int main() {
    Stack<int> s;

    try {
        // Push elements
        s.push(10);
        s.push(20);
        s.push(30);

        cout << "Top of stack: " << s.top() << endl;

        // Pop elements
        s.pop();
        cout << "Top after pop: " << s.top() << endl;

        s.pop();
        s.pop();

        // One more pop to trigger exception
        s.pop();

    } catch (const StackUnderflowException& e) {
        cerr << "Exception: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "Other Exception: " << e.what() << endl;
    }

    return 0;
}
