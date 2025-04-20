#include <iostream>
#include <string>
using namespace std;

// Abstract base class Car
class Car {
protected:
    string model;
    double price;

public:
    // Constructor
    Car(const string& m, double p) : model(m), price(p) {}

    // Get methods
    string getModel() const { return model; }
    double getPrice() const { return price; }

    // Set methods
    void setModel(const string& m) { model = m; }
    
    // Pure virtual function (makes the class abstract)
    virtual void setPrice(double p) = 0;

    // Virtual destructor
    virtual ~Car() {}
};

// Derived class Color
class Color : public Car {
private:
    string color;

public:
    Color(const string& m, double p, const string& c) 
        : Car(m, p), color(c) {}

    // Implementation of abstract method
    void setPrice(double p) override {
        // For Color class, we'll add a 5% premium to the price
        price = p * 1.05;
    }

    // Additional methods for Color
    string getColor() const { return color; }
    void setColor(const string& c) { color = c; }

    void display() const {
        cout << "Color Car - Model: " << model 
             << ", Price: $" << price 
             << ", Color: " << color << endl;
    }
};

// Derived class Company
class Company : public Car {
private:
    string company;

public:
    Company(const string& m, double p, const string& comp) 
        : Car(m, p), company(comp) {}

    // Implementation of abstract method
    void setPrice(double p) override {
        // For Company class, we'll add a fixed $1000 to the price
        price = p + 1000;
    }

    // Additional methods for Company
    string getCompany() const { return company; }
    void setCompany(const string& comp) { company = comp; }

    void display() const {
        cout << "Company Car - Model: " << model 
             << ", Price: $" << price 
             << ", Company: " << company << endl;
    }
};

int main() {
    // Create instances of derived classes
    Color colorCar("Sedan", 20000, "Red");
    Company companyCar("SUV", 30000, "Toyota");

    // Display initial information
    cout << "Initial Car Information:" << endl;
    colorCar.display();
    companyCar.display();
    cout << endl;

    // Change prices using the abstract setPrice method
    colorCar.setPrice(21000);
    companyCar.setPrice(31000);

    // Display updated information
    cout << "After Price Adjustment:" << endl;
    colorCar.display();
    companyCar.display();
    cout << endl;

    // Demonstrate polymorphism
    Car* cars[2];
    cars[0] = new Color("Hatchback", 18000, "Blue");
    cars[1] = new Company("Truck", 40000, "Ford");

    cout << "Using Polymorphism:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "Model: " << cars[i]->getModel() 
             << ", Price: $" << cars[i]->getPrice() << endl;
        
        // Change price polymorphically
        cars[i]->setPrice(cars[i]->getPrice() + 2000);
        cout << "After price increase: $" << cars[i]->getPrice() << endl << endl;
        
        delete cars[i];
    }

    return 0;
}