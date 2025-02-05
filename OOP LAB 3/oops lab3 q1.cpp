#include <iostream>
using namespace std;

class User {
public:
    int Age;
    string Name;
};

int main() {
    User me;
    me.Name = "Teo";
    me.Age = 24;

    cout << "My name is " << me.Name << " and I'm " << me.Age << " years old." << endl;
    return 0;
}
