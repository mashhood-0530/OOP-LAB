#include <iostream>
using namespace std;

class Glass {
public:
    int LiquidLevel;
    
    Glass() {
        LiquidLevel = 200;
    }
    
    void Drink(int milliliters) {
        if (milliliters > 0 && milliliters <= LiquidLevel) {
            LiquidLevel -= milliliters;
        }
        
        if (LiquidLevel < 100) {
            Refill();
        }
    }
    
    void Refill() {
        LiquidLevel = 200;
        cout << "Glass refilled to 200 ml." << endl;
    }
};

int main() {
    Glass x;
    int amount;
    
    cout << "Enter the amount to drink (or a negative number to exit):" << endl;
    while (cin >> amount && amount >= 0) {
        x.Drink(amount);
        cout << "Current liquid level: " << x.LiquidLevel << " ml" << endl;
    }
    
    return 0;
}
