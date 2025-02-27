#include <iostream>
#include <vector>
#include <string>

class Car {
private:
    std::string name;
    int id;

public:
    Car(std::string name, int id) : name(name), id(id) {}

    std::string getName() const {
        return name;
    }

    int getId() const {
        return id;
    }

    ~Car() {
        std::cout << "Car " << name << " (ID: " << id << ") is destroyed." << std::endl;
    }
};


class Garage {
private:
    std::vector<Car*> cars; // Aggregation: Stores pointers to external Car objects

public:
    // Park a car in the garage
    void parkCar(Car* car) {
        cars.push_back(car);
        std::cout << "Car " << car->getName() << " (ID: " << car->getId() << ") parked in the garage." << std::endl;
    }

    // List all cars in the garage
    void listCars() const {
        if (cars.empty()) {
            std::cout << "No cars in the garage." << std::endl;
        } else {
            std::cout << "Cars in the garage:" << std::endl;
            for (const auto& car : cars) {
                std::cout << " - " << car->getName() << " (ID: " << car->getId() << ")" << std::endl;
            }
        }
    }
};

int main() {
    // Create Car objects on the stack
    Car car1("Toyota", 1);
    Car car2("Honda", 2);
    Car car3("Ford", 3);

    // Create a Garage object
    Garage garage;

    // Park cars in the garage
    garage.parkCar(&car1);
    garage.parkCar(&car2);
    garage.parkCar(&car3);

    // List all cars in the garage
    garage.listCars();

    // Note: The cars are destroyed when they go out of scope (end of main)
    std::cout << "End of main(). Cars will be destroyed." << std::endl;

    return 0;
}


//Key Observations

//Destruction Order:
//The Car objects are destroyed after the Garage object goes out of scope at the end of main().
//This demonstrates that the Garage does not control the lifetime of the Car objects.

//Dangling Pointers:
//If the Garage tried to access the Car pointers after they were destroyed, it would result in undefined behavior. This is a potential pitfall of using raw pointers in aggregation.

