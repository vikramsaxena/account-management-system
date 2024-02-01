#ifndef ACCOUNT_VIKRAM_SAHAI_SAXENA_H
#define ACCOUNT_VIKRAM_SAHAI_SAXENA_H

#include "CurrentTime_Vikram_Sahai_Saxena.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Abstract Account class
class Account {
    private:
        static double cashBalance; // account balance
    public:
        Account(); // Constructor
        virtual ~Account(); // Virtual Destructor
        virtual void displayAccountOptions() const; // virtual function to display account options
        void credit(double); // Add an amount to the current balance
        bool debit(double); // Withdraw an amount from the current balance
        double getCashBalance() const; // Get the current balance
        virtual void writeTransactionHistory(const string&, int, double, const string&, bool) const = 0; // Pure virtual function to write transaction history
        virtual void displayTransactionHistory() const = 0; // Pure virtual function to display transaction history
};

#endif