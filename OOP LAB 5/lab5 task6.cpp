#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Structure for menu items
struct MenuItem {
    string name;
    string type; // "drink" or "food"
    double price;
};

// CoffeeShop class
class CoffeeShop {
private:
    const string name;                 // Coffee shop name (constant)
    vector<MenuItem> menu;             // Menu items
    vector<string> orders;             // List of orders

public:
    // Constructor
    CoffeeShop(string shopName, vector<MenuItem> menuItems)
        : name(shopName), menu(menuItems) {}

    // Function to add an order
    string addOrder(string itemName) {
        for (const auto& item : menu) {
            if (item.name == itemName) {
                orders.push_back(itemName);
                return "Order added: " + itemName;
            }
        }
        return "This item is currently unavailable!";
    }

    // Function to fulfill an order
    string fulfillOrder() {
        if (!orders.empty()) {
            string item = orders.front();
            orders.erase(orders.begin());
            return "The " + item + " is ready!";
        }
        return "All orders have been fulfilled";
    }

    // Function to list all orders
    vector<string> listOrders() {
        return orders;
    }

    // Function to calculate the total amount due
    double dueAmount() {
        double total = 0.0;
        for (const auto& order : orders) {
            for (const auto& item : menu) {
                if (item.name == order) {
                    total += item.price;
                    break;
                }
            }
        }
        return total;
    }

    // Function to find the cheapest item
    string cheapestItem() {
        if (menu.empty()) return "Menu is empty!";
        
        double minPrice = numeric_limits<double>::max();
        string cheapest;
        
        for (const auto& item : menu) {
            if (item.price < minPrice) {
                minPrice = item.price;
                cheapest = item.name;
            }
        }
        return cheapest;
    }

    // Function to get drinks only
    vector<string> drinksOnly() {
        vector<string> drinks;
        for (const auto& item : menu) {
            if (item.type == "drink") {
                drinks.push_back(item.name);
            }
        }
        return drinks;
    }

    // Function to get food only
    vector<string> foodOnly() {
        vector<string> foods;
        for (const auto& item : menu) {
            if (item.type == "food") {
                foods.push_back(item.name);
            }
        }
        return foods;
    }

    // Function to display menu (for debugging)
    void displayMenu() {
        cout << "Menu at " << name << ":\n";
        for (const auto& item : menu) {
            cout << "- " << item.name << " (" << item.type << ") - $" << item.price << endl;
        }
    }
};

// Main function
int main() {
    // Creating a sample menu
    vector<MenuItem> menu = {
        {"Espresso", "drink", 2.50},
        {"Latte", "drink", 3.50},
        {"Cappuccino", "drink", 3.00},
        {"Muffin", "food", 2.00},
        {"Sandwich", "food", 4.50},
        {"Cookie", "food", 1.50}
    };

    // Creating a CoffeeShop object
    CoffeeShop myShop("Cafe Delight", menu);

    // Display menu
    myShop.displayMenu();
    
    // Placing orders
    cout << myShop.addOrder("Latte") << endl;
    cout << myShop.addOrder("Muffin") << endl;
    cout << myShop.addOrder("Burger") << endl; // Not on menu

    // Listing orders
    vector<string> orders = myShop.listOrders();
    cout << "\nCurrent orders: ";
    for (const auto& order : orders) {
        cout << order << " ";
    }
    cout << endl;

    // Total amount due
    cout << "Total due: $" << myShop.dueAmount() << endl;

    // Fulfill orders
    cout << myShop.fulfillOrder() << endl;
    cout << myShop.fulfillOrder() << endl;
    cout << myShop.fulfillOrder() << endl;

    // Check cheapest item
    cout << "Cheapest item: " << myShop.cheapestItem() << endl;

    // Drinks only
    vector<string> drinks = myShop.drinksOnly();
    cout << "Drinks available: ";
    for (const auto& drink : drinks) {
        cout << drink << " ";
    }
    cout << endl;

    // Foods only
    vector<string> foods = myShop.foodOnly();
    cout << "Foods available: ";
    for (const auto& food : foods) {
        cout << food << " ";
    }
    cout << endl;

    return 0;
}
