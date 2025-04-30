#include <iostream>
using namespace std;

// Templated base class
template <typename T>
class Base {
protected:
    T a, b;

public:
    Base(T x, T y) : a(x), b(y) {}

    T multiplyBase() const {
        return a * b;
    }

    void printBaseProduct() const {
        cout << "Base multiplication (a * b): " << multiplyBase() << endl;
    }
};

// Templated derived class inheriting from Base<T>
template <typename T>
class Derived : public Base<T> {
private:
    T c, d;

public:
    Derived(T x, T y, T m, T n) : Base<T>(x, y), c(m), d(n) {}

    T multiplyDerived() const {
        return c * d;
    }

    T multiplyAll() const {
        return this->a * this->b * c * d;
    }

    void printDerivedProduct() const {
        cout << "Derived multiplication (c * d): " << multiplyDerived() << endl;
    }

    void printTotalProduct() const {
        cout << "Total multiplication (a * b * c * d): " << multiplyAll() << endl;
    }
};
int main() {
    Derived<int> obj(2, 3, 4, 5); // a=2, b=3, c=4, d=5

    obj.printBaseProduct();       // 2 * 3 = 6
    obj.printDerivedProduct();    // 4 * 5 = 20
    obj.printTotalProduct();      // 2 * 3 * 4 * 5 = 120

    return 0;
}
