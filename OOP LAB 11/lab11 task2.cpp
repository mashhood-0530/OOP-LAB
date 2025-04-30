#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// Custom exception for dimension mismatches
class DimensionMismatchException : public exception {
public:
    const char* what() const noexcept override {
        return "Matrix dimension mismatch.";
    }
};

// Generic Matrix class template
template <typename T>
class Matrix {
private:
    size_t rows, cols;
    vector<vector<T>> data;

public:
    // Constructor: Initializes matrix with given dimensions and optional initial value
    Matrix(size_t r, size_t c, T initial = T()) : rows(r), cols(c), data(r, vector<T>(c, initial)) {}

    // Accessor for number of rows
    size_t numRows() const { return rows; }

    // Accessor for number of columns
    size_t numCols() const { return cols; }

    // Safe element access with bounds checking
    T& at(size_t i, size_t j) {
        if (i >= rows || j >= cols)
            throw out_of_range("Matrix index out of bounds.");
        return data[i][j];
    }

    // Const version of safe element access
    const T& at(size_t i, size_t j) const {
        if (i >= rows || j >= cols)
            throw out_of_range("Matrix index out of bounds.");
        return data[i][j];
    }

    // Operator overloading for matrix addition
    Matrix<T> operator+(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols)
            throw DimensionMismatchException();

        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];

        return result;
    }

    // Operator overloading for matrix multiplication
    Matrix<T> operator*(const Matrix<T>& other) const {
        if (cols != other.rows)
            throw DimensionMismatchException();

        Matrix<T> result(rows, other.cols, T());
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < other.cols; ++j)
                for (size_t k = 0; k < cols; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];

        return result;
    }

    // Friend function for outputting the matrix
    friend ostream& operator<<(ostream& os, const Matrix<T>& m) {
        for (size_t i = 0; i < m.rows; ++i) {
            for (size_t j = 0; j < m.cols; ++j)
                os << m.data[i][j] << " ";
            os << endl;
        }
        return os;
    }
};
int main() {
    try {
        Matrix<int> A(2, 3, 1); // 2x3 matrix filled with 1s
        Matrix<int> B(2, 3, 2); // 2x3 matrix filled with 2s
        Matrix<int> C = A + B;  // Matrix addition
        cout << "Matrix C (A + B):\n" << C << endl;

        Matrix<int> D(3, 2, 3); // 3x2 matrix filled with 3s
        Matrix<int> E = A * D;  // Matrix multiplication
        cout << "Matrix E (A * D):\n" << E << endl;

        // Accessing an element
        cout << "Element at (0,1) in E: " << E.at(0, 1) << endl;

        // Uncommenting the following line will throw an exception due to dimension mismatch
        // Matrix<int> F = A + D;

        // Uncommenting the following line will throw an exception due to out-of-bounds access
        // cout << E.at(5, 5) << endl;

    } catch (const DimensionMismatchException& e) {
        cerr << "Dimension error: " << e.what() << endl;
    } catch (const out_of_range& e) {
        cerr << "Out of range error: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
    }

    return 0;
}
