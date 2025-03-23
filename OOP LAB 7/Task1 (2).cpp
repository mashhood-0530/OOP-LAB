#include <iostream>
#include <string>
using namespace std;

class Account {
protected:
    string accountNumber, accountHolderName, accountType;
    double balance;

public:
    Account(string accNum, string holder, string type, double bal)
        : accountNumber(accNum), accountHolderName(holder), accountType(type), balance(bal) {}

    virtual void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << ". New balance: " << balance << endl;
    }

    virtual bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
            return false;
        }
        balance -= amount;
        cout << "Withdrawn: " << amount << ". New balance: " << balance << endl;
        return true;
    }

    virtual double calculateInterest() { return 0; }

    virtual void printStatement() {
        cout << "Account Statement for " << accountHolderName << endl;
        cout << "Account Type: " << accountType << ", Balance: " << balance << endl;
    }

    virtual void getAccountInfo() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Holder Name: " << accountHolderName << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Balance: " << balance << endl;
    }
};

class SavingsAccount : public Account {
    double interestRate;
    double minimumBalance;

public:
    SavingsAccount(string accNum, string holder, double bal, double rate, double minBal)
        : Account(accNum, holder, "Savings", bal), interestRate(rate), minimumBalance(minBal) {}

    double calculateInterest() override {
        return balance * (interestRate / 100);
    }

    bool withdraw(double amount) override {
        if (balance - amount < minimumBalance) {
            cout << "Cannot withdraw. Minimum balance requirement not met!" << endl;
            return false;
        }
        return Account::withdraw(amount);
    }

    void printStatement() override {
        Account::printStatement();
        cout << "Interest Rate: " << interestRate << "%, Minimum Balance: " << minimumBalance << endl;
    }
};

class CheckingAccount : public Account {
    double overdraftLimit;

public:
    CheckingAccount(string accNum, string holder, double bal, double overdraft)
        : Account(accNum, holder, "Checking", bal), overdraftLimit(overdraft) {}

    bool withdraw(double amount) override {
        if (balance - amount < -overdraftLimit) {
            cout << "Overdraft limit exceeded!" << endl;
            return false;
        }
        return Account::withdraw(amount);
    }

    void printStatement() override {
        Account::printStatement();
        cout << "Overdraft Limit: " << overdraftLimit << endl;
    }
};

class FixedDepositAccount : public Account {
    double fixedInterestRate;
    int maturityDate;

public:
    FixedDepositAccount(string accNum, string holder, double bal, double rate, int maturity)
        : Account(accNum, holder, "Fixed Deposit", bal), fixedInterestRate(rate), maturityDate(maturity) {}

    double calculateInterest() override {
        return balance * (fixedInterestRate / 100);
    }

    bool withdraw(double) override {
        cout << "Withdrawals not allowed until maturity date: " << maturityDate << endl;
        return false;
    }

    void printStatement() override {
        Account::printStatement();
        cout << "Fixed Interest Rate: " << fixedInterestRate << "%, Maturity Date: " << maturityDate << endl;
    }
};

int main() {
    SavingsAccount savings("SA123", "Ali Raza", 5000, 2.5, 1000);
    CheckingAccount checking("CA456", "Ali Raza", 3000, 500);
    FixedDepositAccount fixedDeposit("FD789", "Ali Raza", 10000, 5, 2026);

    cout << "\nAccount Details:\n";
    savings.getAccountInfo();
    checking.getAccountInfo();
    fixedDeposit.getAccountInfo();

    cout << "\nPerforming Transactions:\n";
    savings.deposit(1000);
    savings.withdraw(4500);
    
    checking.withdraw(3400);
    checking.deposit(500);
    
    fixedDeposit.withdraw(2000);

    cout << "\nAccount Statements:\n";
    savings.printStatement();
    checking.printStatement();
    fixedDeposit.printStatement();

    return 0;
}
