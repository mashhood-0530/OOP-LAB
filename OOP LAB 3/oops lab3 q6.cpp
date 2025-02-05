#include <iostream>
#include <vector>
using namespace std;

class Matrix {
private:
    int rows, cols;
    vector<vector<int>> elements;

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        elements.resize(rows, vector<int>(cols, 0));
    }

    int getRows() const {
        return rows;
    }

    int getCols() const {
        return cols;
    }

    void setElement(int i, int j, int value) {
        if (i >= 0 && i < rows && j >= 0 && j < cols) {
            elements[i][j] = value;
        } else {
            cout << "Invalid index" << endl;
        }
    }

    Matrix operator+(const Matrix &other) {
        if (rows != other.rows || cols != other.cols) {
            cout << "Matrices cannot be added" << endl;
            return Matrix(0, 0);
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.elements[i][j] = elements[i][j] + other.elements[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix &other) {
        if (cols != other.rows) {
            cout << "Matrices cannot be multiplied" << endl;
            return Matrix(0, 0);
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    result.elements[i][j] += elements[i][k] * other.elements[k][j];
                }
            }
        }
        return result;
    }

    void printMatrix() const {
        for (const auto &row : elements) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    }
};

int main(int argc, char *argv[]) {
    if (argc < 5) {
        cout << "Usage: ./program rows cols val1 val2 ..." << endl;
        return 1;
    }

    int rows = stoi(argv[1]);
    int cols = stoi(argv[2]);
    Matrix mat(rows, cols);
    
    int index = 3;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (index < argc) {
                mat.setElement(i, j, stoi(argv[index++]));
            }
        }
    }

    cout << "Matrix: " << endl;
    mat.printMatrix();
    return 0;
}
