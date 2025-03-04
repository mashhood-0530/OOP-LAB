#include <iostream>
#include <string>

// Base class for Vehicles
class Vehicles {
protected:
    double price;

public:
    Vehicles(double vehiclePrice)
        : price(vehiclePrice) {}

    virtual ~Vehicles() = default;

    virtual void displayDetails() const {
        std::cout << "Price: $" << price << std::endl;
    }
};

// Derived class for Car
class Car : public Vehicles {
protected:
    int seatingCapacity;
    int numberOfDoors;
    std::string fuelType;

public:
    Car(double vehiclePrice, int capacity, int doors, const std::string& fuel)
        : Vehicles(vehiclePrice), seatingCapacity(capacity), numberOfDoors(doors), fuelType(fuel) {}

    void displayDetails() const override {
        Vehicles::displayDetails();
        std::cout << "Seating Capacity: " << seatingCapacity << std::endl;
        std::cout << "Number of Doors: " << numberOfDoors << std::endl;
        std::cout << "Fuel Type: " << fuelType << std::endl;
    }
};

// Derived class for Motorcycle
class Motorcycle : public Vehicles {
protected:
    int numberOfCylinders;
    int numberOfGears;
    int numberOfWheels;

public:
    Motorcycle(double vehiclePrice, int cylinders, int gears, int wheels)
        : Vehicles(vehiclePrice), numberOfCylinders(cylinders), numberOfGears(gears), numberOfWheels(wheels) {}

    void displayDetails() const override {
        Vehicles::displayDetails();
        std::cout << "Number of Cylinders: " << numberOfCylinders << std::endl;
        std::cout << "Number of Gears: " << numberOfGears << std::endl;
        std::cout << "Number of Wheels: " << numberOfWheels << std::endl;
    }
};

// Subclass for Audi (derived from Car)
class Audi : public Car {
private:
    std::string modelType;

public:
    Audi(double vehiclePrice, int capacity, int doors, const std::string& fuel, const std::string& model)
        : Car(vehiclePrice, capacity, doors, fuel), modelType(model) {}

    void displayDetails() const override {
        std::cout << "Audi Car Details:" << std::endl;
        Car::displayDetails();
        std::cout << "Model Type: " << modelType << std::endl;
    }
};

// Subclass for Yamaha (derived from Motorcycle)
class Yamaha : public Motorcycle {
private:
    std::string makeType;

public:
    Yamaha(double vehiclePrice, int cylinders, int gears, int wheels, const std::string& make)
        : Motorcycle(vehiclePrice, cylinders, gears, wheels), makeType(make) {}

    void displayDetails() const override {
        std::cout << "Yamaha Motorcycle Details:" << std::endl;
        Motorcycle::displayDetails();
        std::cout << "Make Type: " << makeType << std::endl;
    }
};

int main() {
    // Create an Audi car object
    Audi audi(50000, 5, 4, "Petrol", "A4");

    // Create a Yamaha motorcycle object
    Yamaha yamaha(15000, 2, 5, 2, "YZF-R1");

    // Display details of the Audi car
    audi.displayDetails();
    std::cout << "-------------------" << std::endl;

    // Display details of the Yamaha motorcycle
    yamaha.displayDetails();
    std::cout << "-------------------" << std::endl;

    return 0;
}