#ifndef BANKACCOUNT_VIKRAM_SAHAI_SAXENA_H
#define BANKACCOUNT_VIKRAM_SAHAI_SAXENA_H

#include "Account_Vikram_Sahai_Saxena.h"

// Derived class BankAccount
class BankAccount : public Account {
    public:
        BankAccount(); // Constructor
        virtual ~BankAccount(); // Destructor
        void displayAccountOptions() const; // display bank account options
        void displayAccountBalance() const; // display bank account balance
        void depositMoney(CurrentTime*); // deposit money to the bank balance
        void withdrawMoney(CurrentTime*); // withdraw money from the bank balance
        void writeTransactionHistory(const string&, int, double, const string&, bool) const; // Write Bank Account transaction history
        void displayTransactionHistory() const; // Display Bank Account transaction history
};
#endif