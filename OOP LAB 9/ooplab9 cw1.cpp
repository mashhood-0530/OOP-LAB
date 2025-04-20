#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

/*
    Wallet class encapsulates all financial operations and maintains:
    - Current balance (private)
    - Daily deposit/withdrawal tracking (private)
    - Maximum limits (constant)
    Only exposes deposit/withdraw/check balance operations
*/
class Wallet {
private:
    double balance;
    double dailyDeposited;
    double dailyWithdrawn;
    const double MAX_DAILY_DEPOSIT = 10000.0;
    const double MAX_DAILY_WITHDRAWAL = 5000.0;

    // Helper to validate positive amount
    void validateAmount(double amount) const {
        if (amount <= 0) {
            throw invalid_argument("Amount must be positive");
        }
    }

public:
    Wallet() : balance(0.0), dailyDeposited(0.0), dailyWithdrawn(0.0) {}

    // Deposit money into wallet with daily limit check
    void deposit(double amount) {
        validateAmount(amount);
        
        if (dailyDeposited + amount > MAX_DAILY_DEPOSIT) {
            throw runtime_error("Daily deposit limit exceeded ($" + 
                               to_string(MAX_DAILY_DEPOSIT) + ")");
        }

        balance += amount;
        dailyDeposited += amount;
    }

    // Withdraw money from wallet with balance and daily limit checks
    void withdraw(double amount) {
        validateAmount(amount);
        
        if (amount > balance) {
            throw runtime_error("Insufficient funds");
        }

        if (dailyWithdrawn + amount > MAX_DAILY_WITHDRAWAL) {
            throw runtime_error("Daily withdrawal limit exceeded ($" + 
                               to_string(MAX_DAILY_WITHDRAWAL) + ")");
        }

        balance -= amount;
        dailyWithdrawn += amount;
    }

    // Get current balance
    double getBalance() const {
        return balance;
    }

    // Reset daily counters (would be called by a daily scheduler in real system)
    void resetDailyLimits() {
        dailyDeposited = 0.0;
        dailyWithdrawn = 0.0;
    }
};

/*
    User class encapsulates user details and contains a Wallet
    - Wallet is private and can't be accessed directly
    - Only exposes necessary wallet operations through methods
*/
class User {
private:
    string userId;
    string name;
    Wallet wallet;  // Composition - User HAS-A Wallet

public:
    User(const string& id, const string& userName) 
        : userId(id), name(userName) {}

    // Forward deposit to wallet
    void deposit(double amount) {
        wallet.deposit(amount);
    }

    // Forward withdraw to wallet
    void withdraw(double amount) {
        wallet.withdraw(amount);
    }

    // Forward balance check to wallet
    double checkBalance() const {
        return wallet.getBalance();
    }

    // Display user information
    void displayInfo() const {
        cout << "User ID: " << userId << "\n"
             << "Name: " << name << "\n"
             << "Balance: $" << checkBalance() << "\n";
    }
};

/*
    Demonstration of the system with:
    - Multiple user scenarios
    - Valid operations
    - Error handling for invalid operations
*/
int main() {
    try {
        cout << "=== Digital Wallet System ===\n\n";

        // Create users
        User alamghir("U1001", "Alamghir Khan");
        User babar("U1002", "Babar Azam");

        // Initial state
        cout << "Initial balances:\n";
        alamghir.displayInfo();
        babar.displayInfo();
        cout << endl;

        // Test valid deposits
        cout << "Alamghir deposits $500\n";
        alamghir.deposit(500);
        alamghir.displayInfo();
        cout << endl;

        cout << "Babar deposits $1000\n";
        babar.deposit(1000);
        babar.displayInfo();
        cout << endl;

        // Test valid withdrawals
        cout << "Alamghir withdraws $200\n";
        alamghir.withdraw(200);
        alamghir.displayInfo();
        cout << endl;

        // Test error scenarios
        cout << "Attempting invalid operations:\n";

        try {
            cout << "Babar tries to withdraw $1200 (more than balance)\n";
            babar.withdraw(1200);
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }

        try {
            cout << "Alamghir tries to deposit $-100 (negative amount)\n";
            alamghir.deposit(-100);
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }

        try {
            cout << "Alamghir tries to deposit $10000 (would exceed daily limit with previous $500 deposit)\n";
            alamghir.deposit(10000);
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }

        // Final balances
        cout << "\nFinal balances:\n";
        alamghir.displayInfo();
        babar.displayInfo();

    } catch (const exception& e) {
        cerr << "System error: " << e.what() << endl;
        return 1;
    }

    return 0;
}