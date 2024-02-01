#include "BankAccount_Vikram_Sahai_Saxena.h"

// Constructor implementation
BankAccount::BankAccount() {}

// Destructor implementation
BankAccount::~BankAccount() {}

// Display the menu options for the bank account
void BankAccount::displayAccountOptions() const {
    cout << "Please select an option:" << endl;
    cout << "1. View account balance" << endl;
    cout << "2. Deposit money" << endl;
    cout << "3. Withdraw money" << endl;
    cout << "4. Print out history" << endl;
    cout << "5. Return to previous menu" << endl << endl;
}

// Display the current bank account balance
void BankAccount::displayAccountBalance() const {
    cout << "You have $" << fixed << setprecision(2) << getCashBalance() <<" in your bank account." << endl << endl;
}

// Deposit money into the account
void BankAccount::depositMoney(CurrentTime* currentTime) {
    cout << "Please select the amount you wish to deposit: ";
    double deposit;
    cin >> deposit;
    if (0 >= deposit) {
        cout << "Please enter an amount greater than zero." << endl << endl;
        return;
    }
    credit(deposit);
    writeTransactionHistory("", 1, deposit, currentTime->getCurrentMMDDYYYY(), false);
    cout << endl << endl;
}

// Withdraw money into the account
void BankAccount::withdrawMoney(CurrentTime* currentTime) {
    cout << "Please select the amount you wish to withdraw: ";
    double withdraw;
    cin >> withdraw;
    if (0 >= withdraw) {
        cout << "Please enter an amount greater than zero." << endl << endl;
        return;
    }
    if (debit(withdraw)) {
        writeTransactionHistory("", 1, withdraw, currentTime->getCurrentMMDDYYYY(), true);
    }
    cout << endl << endl;
}

// Write transaction to the bank transaction history file
void BankAccount::writeTransactionHistory(const string& symbol, int shares, double pricePerShare, const string& time, bool isWithdrawal) const {
    ofstream file;
    file.open("bank_transaction_history.txt", fstream::app);
    string withdrawalOrDeposit = (isWithdrawal) ? "Withdrawal" : "Deposit" ;
    file << left << setw(20) << withdrawalOrDeposit << "$" << left << setw(19) << fixed << setprecision(2) << shares * pricePerShare << left << setw(20) << time;
    file << "$" << left << setw(19) << getCashBalance() << endl;
    file.close();
}

// Display the transaction history from the bank transaction history file
void BankAccount::displayTransactionHistory() const {
    ifstream file("bank_transaction_history.txt");
    if (!file.is_open()) {
        cerr << "Failed to open bank_transaction_history.txt" << endl;
        return;
    }
    cout << left << setw(20) << "Event" << left << setw(20) << "Amount" << left << setw(20) << "Date" << left << setw(20) << "Balance" << endl;
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
    cout << endl;
}