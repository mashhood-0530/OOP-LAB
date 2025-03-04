#include <iostream>
#include <vector>
#include <string>

// Base class for BankAccount
class BankAccount {
protected:
    std::string accountNumber;
    double balance;

public:
    BankAccount(const std::string& accNum, double initialBalance)
        : accountNumber(accNum), balance(initialBalance) {}

    virtual ~BankAccount() = default;

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        } else {
            std::cout << "Insufficient funds!" << std::endl;
        }
    }

    double getBalance() const {
        return balance;
    }

    virtual void display() const {
        std::cout << "Account Number: " << accountNumber << ", Balance: $" << balance << std::endl;
    }
};

// Derived class for SavingsAccount
class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(const std::string& accNum, double initialBalance, double rate)
        : BankAccount(accNum, initialBalance), interestRate(rate) {}

    void applyMonthlyInterest() {
        double interest = balance * interestRate / 12;
        deposit(interest);
    }

    void display() const override {
        std::cout << "Savings Account - ";
        BankAccount::display();
    }
};

// Derived class for CheckingAccount
class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(const std::string& accNum, double initialBalance, double limit)
        : BankAccount(accNum, initialBalance), overdraftLimit(limit) {}

    void withdraw(double amount) override {
        if (amount <= balance + overdraftLimit) {
            balance -= amount;
            if (balance < 0) {
                std::cout << "Overdraft alert! Balance: $" << balance << std::endl;
            }
        } else {
            std::cout << "Overdraft limit exceeded!" << std::endl;
        }
    }

    void display() const override {
        std::cout << "Checking Account - ";
        BankAccount::display();
    }
};

// Derived class for BusinessAccount
class BusinessAccount : public BankAccount {
private:
    double corporateTaxRate;

public:
    BusinessAccount(const std::string& accNum, double initialBalance, double taxRate)
        : BankAccount(accNum, initialBalance), corporateTaxRate(taxRate) {}

    void deposit(double amount) override {
        double tax = amount * corporateTaxRate;
        BankAccount::deposit(amount - tax);
    }

    void display() const override {
        std::cout << "Business Account - ";
        BankAccount::display();
    }
};

// Base class for UserRole
class UserRole {
public:
    virtual ~UserRole() = default;
    virtual void performAction(BankAccount* account) = 0;
};

// Derived class for Customer
class Customer : public UserRole {
public:
    void performAction(BankAccount* account) override {
        std::cout << "Customer performing action:" << std::endl;
        account->deposit(100);
        account->withdraw(50);
        account->display();
    }
};

// Derived class for Teller
class Teller : public UserRole {
public:
    void performAction(BankAccount* account) override {
        std::cout << "Teller performing action:" << std::endl;
        account->deposit(200);
        account->withdraw(100);
        account->display();
    }
};

// Derived class for Manager
class Manager : public UserRole {
public:
    void performAction(BankAccount* account) override {
        std::cout << "Manager performing action:" << std::endl;
        account->deposit(500);
        account->withdraw(250);
        account->display();
    }
};

int main() {
    // Creating a collection of accounts
    std::vector<BankAccount*> accounts = {
        new SavingsAccount("SA001", 1000, 0.05),
        new CheckingAccount("CA001", 2000, 500),
        new BusinessAccount("BA001", 5000, 0.1)
    };

    // Creating a collection of user roles
    std::vector<UserRole*> roles = {
        new Customer(),
        new Teller(),
        new Manager()
    };

    // Demonstrating polymorphism and dynamic dispatch
    for (auto* account : accounts) {
        for (auto* role : roles) {
            role->performAction(account);
        }
    }

    // Clean up
    for (auto* account : accounts) {
        delete account;
    }
    for (auto* role : roles) {
        delete role;
    }

    return 0;
}