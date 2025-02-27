#include <iostream>
#include <ctime>

using namespace std;

// Blend class
class Blend {
public:
    void blendJuice() {
        cout << "Blending juice...\n";
        for (int i = 1; i <= 5; ++i) {  // Simulating blending process for ~5 seconds
            cout << "Blending... " << i << " sec\n";
            delay(1); // Delay for 1 second
        }
        cout << "Blending complete!\n";
    }

private:
    void delay(int seconds) {
        clock_t start_time = clock();
        while (clock() < start_time + seconds * CLOCKS_PER_SEC); // Busy wait
    }
};

// Grind class
class Grind {
public:
    void grindJuice() {
        cout << "Grinding juice...\n";
        delay(5); // Simulating grinding process for 5 seconds
        cout << "Grinding complete!\n";
    }

private:
    void delay(int seconds) {
        clock_t start_time = clock();
        while (clock() < start_time + seconds * CLOCKS_PER_SEC); // Busy wait
    }
};

// JuiceMaker class (composition of Blend and Grind)
class JuiceMaker {
private:
    Blend blender;
    Grind grinder;

public:
    void makeJuice() {
        cout << "Starting juice-making process...\n";
        
        // Step 1: Blending
        blender.blendJuice();
        
        // Step 2: Grinding
        grinder.grindJuice();
        
        cout << "Juice is ready! Enjoy!\n";
    }
};

// Main function
int main() {
    JuiceMaker juicer;
    juicer.makeJuice();
    return 0;
}
