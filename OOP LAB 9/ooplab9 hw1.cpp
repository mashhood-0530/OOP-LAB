#include <iostream>
using namespace std;

// Abstract base class
class Shape {
public:
    // Pure virtual function making this class abstract
    virtual double getArea() const = 0;
    
    // Virtual destructor
    virtual ~Shape() {}
};

// Derived class Rectangle
class Rectangle : public Shape {
private:
    double length;
    double width;
    
public:
    Rectangle(double l, double w) : length(l), width(w) {}
    
    double getArea() const override {
        return length * width;
    }
};

// Derived class Triangle
class Triangle : public Shape {
private:
    double base;
    double height;
    
public:
    Triangle(double b, double h) : base(b), height(h) {}
    
    double getArea() const override {
        return 0.5 * base * height;
    }
};

int main() {
    // Create objects of derived classes
    Rectangle rect(5.0, 3.0);
    Triangle tri(4.0, 6.0);
    
    // Calculate and display areas
    cout << "Area of Rectangle: " << rect.getArea() << endl;
    cout << "Area of Triangle: " << tri.getArea() << endl;
    
    // Using base class pointers
    Shape* shapes[2];
    shapes[0] = new Rectangle(7.0, 2.0);
    shapes[1] = new Triangle(3.0, 5.0);
    
    cout << "\nUsing base class pointers:" << endl;
    cout << "Area of Rectangle: " << shapes[0]->getArea() << endl;
    cout << "Area of Triangle: " << shapes[1]->getArea() << endl;
    
    // Clean up
    delete shapes[0];
    delete shapes[1];
    
    return 0;
}