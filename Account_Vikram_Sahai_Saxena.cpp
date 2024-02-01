#include "Account_Vikram_Sahai_Saxena.h"

double Account::cashBalance = 10000; // Initializing the cash balance to $10000

// Constructor implementation
Account::Account() {
    ifstream file("portfolio_history.txt");
    if (!file.is_open()) {
        cerr << "Error: Failed to open portfolio_history.txt" << endl;
    } else {
        string line, totalPortfolioValue, currentBalance;
        while (getline(file, line)) {
            stringstream ss(line);
            ss >> totalPortfolioValue >> currentBalance;
            cashBalance = stod(currentBalance);
        }
        file.close();
    }
}

// Destructor implementation
Account::~Account() {}

// Display Account options
void Account::displayAccountOptions() const {
    cout << "Please select an account to access:" << endl;
    cout << "1. Stock Portfolio Account" << endl;
    cout << "2. Bank Account" << endl;
    cout << "3. Exit" << endl << endl;
}

// Add money to the balance
void Account::credit(double amount) {
    cashBalance += amount;
}

// Withdraw money from the balance
bool Account::debit(double amount) {
    if (amount > cashBalance) {
        cerr << "Debit amount exceeded account balance." << endl;
        return false;
    }
    cashBalance -= amount;
    return true;
}

// Get the cash balance
double Account::getCashBalance() const{
    return cashBalance;
}