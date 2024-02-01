#include "BankAccount_Vikram_Sahai_Saxena.h"
#include "StockAccount_Vikram_Sahai_Saxena.h"
#include <vector>

int main() {
    // Main menu option
    int option = 0;

    // Vector of Account pointers to hold different account types
    vector<Account*> accounts;
    accounts.push_back(new StockAccount());
    accounts.push_back(new BankAccount());

     // Get the current time instance
    CurrentTime* currentTime = CurrentTime::getInstance();

    cout << "Welcome to the Account Management System." << endl;

    while (3 != option) {
        // Display account options
        accounts[0]->Account::displayAccountOptions();

        cout << "Option: ";
        cin >> option;
        switch (option) {
            case 1: // Stock Portfolio Account
                {
                    cout << "Stock Portfolio Account" << endl << endl;
                    int stockOption = 0;
                    while (8 != stockOption) {
                        accounts[0]->displayAccountOptions();
                        cout << "Option: ";
                        cin >> stockOption;
                        switch (stockOption) {
                            case 1: // Display the price for a stock symbol
                                {   
                                    dynamic_cast<StockAccount*>(accounts[0])->displayStockPrice();
                                    break;
                                }
                            case 2: // Display the current portfolio
                                {
                                    dynamic_cast<StockAccount*>(accounts[0])->displayStockPortfolio();
                                    break;
                                }
                            case 3: // Buy shares
                                {
                                    dynamic_cast<StockAccount*>(accounts[0])->buyShares(dynamic_cast<BankAccount*>(accounts[1]), currentTime);
                                    break;
                                }
                            case 4: // Sell shares
                                {
                                    dynamic_cast<StockAccount*>(accounts[0])->sellShares(dynamic_cast<BankAccount*>(accounts[1]), currentTime);
                                    break;
                                }
                            case 5: // View a graph for the portfolio value
                                {
                                    dynamic_cast<StockAccount*>(accounts[0])->plotGraph();
                                    break;
                                }
                            case 6: // View transaction history
                                {
                                    accounts[0]->displayTransactionHistory();
                                    break;
                                }
                            case 7: // Select sorting method
                                {
                                    dynamic_cast<StockAccount*>(accounts[0])->selectSortOption();
                                    break;
                                }
                            case 8: // Return to previous menu
                                break;
                            default:
                                cout << "Option is not valid!" << endl;
                        }
                    }
                    break;
                }
            case 2: // Bank Account
                {
                    cout << "Bank Account" << endl << endl;
                    int bankOption = 0;
                    while (bankOption != 5) {
                        accounts[1]->displayAccountOptions();
                        cout << "Option: ";
                        cin >> bankOption;
                        switch (bankOption) {
                            case 1: // View account balance
                                {   
                                    dynamic_cast<BankAccount*>(accounts[1])->displayAccountBalance();
                                    break;
                                }
                            case 2: // Deposit money
                                {
                                    dynamic_cast<BankAccount*>(accounts[1])->depositMoney(currentTime);
                                    break;
                                }
                            case 3: // Withdraw money
                                {
                                    dynamic_cast<BankAccount*>(accounts[1])->withdrawMoney(currentTime);
                                    break;
                                }
                            case 4: // Print out history
                                {
                                    accounts[1]->displayTransactionHistory();
                                    break;
                                }
                            case 5: // Return to previous menu
                                break;
                            default:
                                cout << "Choice is not valid!" << endl;
                        }
                    }
                    break;
                }
            case 3: // Exit the program
                {   
                    // Clean up allocated memory
                    for (auto account : accounts) {
                        delete account;
                    }
                    delete currentTime;
                    break;
                }
            default: 
                cout << "Choice is not valid!" << endl;
        }
    }
    return 0;
}