#include <iostream>
#include <string>
#include <vector>

// Base class for Employee
class Employee {
protected:
    int id;
    std::string name;

public:
    Employee(int empId, const std::string& empName)
        : id(empId), name(empName) {}

    virtual ~Employee() = default;

    virtual void display() const {
        std::cout << "ID: " << id << ", Name: " << name << std::endl;
    }
};

// Abstract interface for taking orders
class IOrderTaker {
public:
    virtual ~IOrderTaker() = default;
    virtual void takeOrder(const std::string& order) = 0;
};

// Abstract interface for preparing orders
class IOrderPreparer {
public:
    virtual ~IOrderPreparer() = default;
    virtual void prepareOrder(const std::string& order) = 0;
};

// Abstract interface for generating bills
class IBiller {
public:
    virtual ~IBiller() = default;
    virtual void generateBill(double amount) = 0;
};

// Waiter class (implements IOrderTaker)
class Waiter : public Employee, public IOrderTaker {
public:
    Waiter(int empId, const std::string& empName)
        : Employee(empId, empName) {}

    void takeOrder(const std::string& order) override {
        std::cout << "Waiter " << name << " is taking order: " << order << std::endl;
    }
};

// Chef class (implements IOrderPreparer)
class Chef : public Employee, public IOrderPreparer {
public:
    Chef(int empId, const std::string& empName)
        : Employee(empId, empName) {}

    void prepareOrder(const std::string& order) override {
        std::cout << "Chef " << name << " is preparing order: " << order << std::endl;
    }
};

// Cashier class (implements IBiller)
class Cashier : public Employee, public IBiller {
public:
    Cashier(int empId, const std::string& empName)
        : Employee(empId, empName) {}

    void generateBill(double amount) override {
        std::cout << "Cashier " << name << " is generating a bill for $" << amount << std::endl;
    }
};

// Manager class (implements multiple roles: IOrderTaker and IBiller)
class Manager : public Employee, public IOrderTaker, public IBiller {
public:
    Manager(int empId, const std::string& empName)
        : Employee(empId, empName) {}

    void takeOrder(const std::string& order) override {
        std::cout << "Manager " << name << " is taking order: " << order << std::endl;
    }

    void generateBill(double amount) override {
        std::cout << "Manager " << name << " is generating a bill for $" << amount << std::endl;
    }
};

// Base class for Menu
class Menu {
protected:
    std::string name;
    double baseCost;

public:
    Menu(const std::string& menuName, double cost)
        : name(menuName), baseCost(cost) {}

    virtual ~Menu() = default;

    virtual double calculateTotalCost() const {
        return baseCost;
    }

    virtual void display() const {
        std::cout << "Menu: " << name << ", Base Cost: $" << baseCost << std::endl;
    }
};

// Derived class for FoodMenu
class FoodMenu : public Menu {
public:
    FoodMenu(const std::string& menuName, double cost)
        : Menu(menuName, cost) {}

    double calculateTotalCost() const override {
        // Apply combo discount (e.g., 10% off)
        return baseCost * 0.9;
    }

    void display() const override {
        std::cout << "Food Menu - ";
        Menu::display();
        std::cout << "Total Cost (after combo discount): $" << calculateTotalCost() << std::endl;
    }
};

// Derived class for BeverageMenu
class BeverageMenu : public Menu {
private:
    double taxRate; // e.g., 0.1 for 10% tax

public:
    BeverageMenu(const std::string& menuName, double cost, double tax)
        : Menu(menuName, cost), taxRate(tax) {}

    double calculateTotalCost() const override {
        return baseCost * (1 + taxRate);
    }

    void display() const override {
        std::cout << "Beverage Menu - ";
        Menu::display();
        std::cout << "Total Cost (after tax): $" << calculateTotalCost() << std::endl;
    }
};

int main() {
    // Create employees
    Waiter waiter(1, "Mashhood");
    Chef chef(2, "Abdullah");
    Cashier cashier(3, "Rafay");
    Manager manager(4, "Aakif");

    // Create menus
    FoodMenu foodMenu("Pizza Combo", 20.0);
    BeverageMenu beverageMenu("Soft Drinks", 5.0, 0.1);

    // Demonstrate employee roles
    std::vector<IOrderTaker*> orderTakers = { &waiter, &manager };
    for (auto* orderTaker : orderTakers) {
        orderTaker->takeOrder("Large Pizza");
    }

    chef.prepareOrder("Large Pizza");

    std::vector<IBiller*> billers = { &cashier, &manager };
    for (auto* biller : billers) {
        biller->generateBill(25.0);
    }

    // Demonstrate menus
    std::vector<Menu*> menus = { &foodMenu, &beverageMenu };
    for (auto* menu : menus) {
        menu->display();
    }

    return 0;
}