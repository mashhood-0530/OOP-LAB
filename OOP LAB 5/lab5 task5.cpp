#include <iostream>

using namespace std;

class Car {
private:
    int engine_horsepower;
    int seating_capacity;
    mutable int no_of_speakers;  // `mutable` allows modification in a const function

public:
    // Constructor
    Car(int hp, int seats, int speakers)
        : engine_horsepower(hp), seating_capacity(seats), no_of_speakers(speakers) {}

    // Constant function to modify attributes using `mutable`
    void updateCarAttributes(int new_hp, int new_seats, int new_speakers) const {
        // Cannot modify engine_horsepower and seating_capacity since they are not mutable
        no_of_speakers = new_speakers;  
        cout << "Updated attributes (only speakers modified in const function):\n";
        displayCar();
    }

    // Display function
    void displayCar() const {
        cout << "Engine Horsepower: " << engine_horsepower << endl;
        cout << "Seating Capacity: " << seating_capacity << endl;
        cout << "Number of Speakers: " << no_of_speakers << endl;
    }
};

int main() {
    // Creating a Car object
    Car myCar(250, 5, 6);
    
    cout << "Original Car Attributes:\n";
    myCar.displayCar();

    // Trying to update values via const function
    myCar.updateCarAttributes(300, 7, 8);

    return 0;
}
