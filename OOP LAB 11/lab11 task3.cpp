#include <iostream>
#include <stdexcept>

using namespace std;

// Custom exception for invalid index access
class ArrayIndexOutOfBounds : public exception {
public:
    const char* what() const noexcept override {
        return "ArrayIndexOutOfBounds: Index is out of valid array range.";
    }
};

// Template class for safe array
template <typename T>
class SafeArray {
private:
    T* arr;
    size_t size;

public:
    // Constructor
    SafeArray(size_t s) : size(s) {
        arr = new T[size];
    }

    // Destructor
    ~SafeArray() {
        delete[] arr;
    }

    // Size getter
    size_t length() const {
        return size;
    }

    // Overloaded subscript operator with bounds checking
    T& operator[](int index) {
        if (index < 0 || index >= static_cast<int>(size)) {
            throw ArrayIndexOutOfBounds();
        }
        return arr[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= static_cast<int>(size)) {
            throw ArrayIndexOutOfBounds();
        }
        return arr[index];
    }
};
int main() {
    try {
        SafeArray<int> myArray(5);

        // Fill array
        for (int i = 0; i < myArray.length(); ++i) {
            myArray[i] = i * 10;
        }

        // Print array
        cout << "SafeArray contents:\n";
        for (int i = 0; i < myArray.length(); ++i) {
            cout << "myArray[" << i << "] = " << myArray[i] << endl;
        }

        // Access out-of-bounds index
        cout << "Attempting to access invalid index..." << endl;
        cout << myArray[10] << endl; // This should throw

    } catch (const ArrayIndexOutOfBounds& e) {
        cerr << "Exception: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "Other Exception: " << e.what() << endl;
    }

    return 0;
}
