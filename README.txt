Name: Vikram Sahai Saxena
NetID: vs799

Layout of the programs:
--------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------

Source code files
--------------------------------------------------------------------------------------------------------
1. Account.h : header file containing an Abstract Account class, its members and prototypes for an account.
2. Account.cpp : program containing the implementation of the Account functions.
3. StockAccount.h : header file containing StockAccount class, its members and prototypes for a stock account.
It inherits public member functions of Account class.
4. StockAccount.cpp : program containing the implementation of the StockAccount functions.
5. BankAccount.h : header file containing BankAccount class, its members and prototypes for a checking account.
It inherits public member functions of Account class.
6. BankAccount.cpp : program containing the implementation of the CheckingAccount functions.
7. CurrentTime.h : header file containing Singleton CurrentTime class, its members and prototypes for getting the current date/time.
8. CurrentTime.cpp : program containing the implementation of the CurrentTime functions.
9. plotGraph.R : R program containing the code for plotting a difference in proftfolio value over time
10. main.cpp : program containing the main() function to test the functionality of the account management system.
11. Result1.txt : Set 1 for Stock symbols and their price per share.
12. Result2.txt : Set 2 for Stock symbols and their price per share.


Output files
--------------------------------------------------------------------------------------------------------
1. bank_transaction_history.txt : stores the bank transaction details (Event, Amount, Date, Balance)
2. stock_transaction_history.txt : stores the stock transaction details (Event, Symbol, Number of Shares, Price per share, Total Value, Time)
3. portfolio_history.txt : contains the portfolio information on program exit (Total portfolio value, Balance, Date/Time).
4. Rplots.pdf: contains plots for difference in portfolio value over time and actual portfolio over time.


How to compile main_Vikram_Sahai_Saxena.cpp
---------------------------------------------------------------------------------------------------------
1. Open terminal/cmd and navigate to the location where main.cpp is present. This is done using 
cd <Path name> command.
2. Enter the following command in terminal/cmd: 
g++ -std=c++11 -g main_Vikram_Sahai_Saxena.cpp Account_Vikram_Sahai_Saxena.cpp BankAccount_Vikram_Sahai_Saxena.cpp StockAccount_Vikram_Sahai_Saxena.cpp CurrentTime_Vikram_Sahai_Saxena.cpp -o main_Vikram_Sahai_Saxena


How to run main_Vikram_Sahai_Saxena.cpp
---------------------------------------------------------------------------------------------------------
1. After successfully compiling main_Vikram_Sahai_Saxena.cpp, run the following command:
./main_Vikram_Sahai_Saxena.cpp


Sample output of main_Vikram_Sahai_Saxena.cpp
---------------------------------------------------------------------------------------------------------
g++ -std=c++11 -g main_Vikram_Sahai_Saxena.cpp Account_Vikram_Sahai_Saxena.cpp BankAccount_Vikram_Sahai_Saxena.cpp StockAccount_Vikram_Sahai_Saxena.cpp CurrentTime_Vikram_Sahai_Saxena.cpp -o main_Vikram_Sahai_Saxena
./main_Vikram_Sahai_Saxena
Welcome to the Account Management System.
Please select an account to access:
1. Stock Portfolio Account
2. Bank Account
3. Exit

Option: 1
Stock Portfolio Account

Please select an option:
1. Display the price for a stock symbol
2. Display the current portfolio
3. Buy shares
4. Sell shares
5. View a graph for the portfolio value
6. View transaction history
7. Select sorting method
8. Return to previous menu

Option: 2
Cash Balance = $4200
Company-Symbol      Number              Price-per-share     Total value         
GOOG                10                  $569.96             $5699.64            
Total portfolio value: $9899.64

Please select an option:
1. Display the price for a stock symbol
2. Display the current portfolio
3. Buy shares
4. Sell shares
5. View a graph for the portfolio value
6. View transaction history
7. Select sorting method
8. Return to previous menu

Option: 3
Please enter the stock symbol you wish to purchase: FRE
Please enter the number of shares: 10
Please enter the maximum amount you are willing to pay per share: 20.75
You have purchased 10 shares of FRE at $20.75 each for a total of $207.50

Please select an option:
1. Display the price for a stock symbol
2. Display the current portfolio
3. Buy shares
4. Sell shares
5. View a graph for the portfolio value
6. View transaction history
7. Select sorting method
8. Return to previous menu

Option: 2
Cash Balance = $3992.50
Company-Symbol      Number              Price-per-share     Total value         
GOOG                10                  $568.96             $5689.64            
FRE                 10                  $2.14               $21.40              
Total portfolio value: $9703.54

Please select an option:
1. Display the price for a stock symbol
2. Display the current portfolio
3. Buy shares
4. Sell shares
5. View a graph for the portfolio value
6. View transaction history
7. Select sorting method
8. Return to previous menu

Option: 8
Please select an account to access:
1. Stock Portfolio Account
2. Bank Account
3. Exit

Option: 3