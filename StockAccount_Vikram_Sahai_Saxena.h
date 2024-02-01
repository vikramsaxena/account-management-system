#ifndef STOCKACCOUNT_VIKRAM_SAHAI_SAXENA_H
#define STOCKACCOUNT_VIKRAM_SAHAI_SAXENA_H

#include "Account_Vikram_Sahai_Saxena.h"
#include "BankAccount_Vikram_Sahai_Saxena.h"
#include <cstdlib>
#include <ctime>
#include <map>

// Node class for use in the Doubly Linked List
class Node {
    friend class DoublyLinkedList;
    friend class SortBubble;
    friend class SortSelection;
private:
    string symbol; // Stock symbol
    int shares; // Number of shares
    Node* next; // Pointer to next node
    Node* prev; // Pointer to previous node
public:
    Node(string, int); // Constructor
    int getShares() const;  // Get the number of shares
    static void swapNodes(Node**, Node*, Node*); // Swap two nodes in the list
};

// Strategy Interface for sorting
class SortImpl {
public:
    virtual ~SortImpl(); // Virtual destructor
    virtual void sort(Node*, map<string, double>) const = 0; // Pure virtual sort function
};

// Concrete Strategy for Bubble Sort
class SortBubble : public SortImpl {
public:
    virtual ~SortBubble(); // Destructor
    void sort(Node*, map<string, double>) const; // Bubble sort implementation
};

// Concrete Strategy for Selection Sort
class SortSelection : public SortImpl {
public:
    virtual ~SortSelection(); // Destructor
    void sort(Node*, map<string, double>) const; // Selection sort implementation
};

// Context Class for strategy pattern
class Context {
    friend class DoublyLinkedList;
private:
    SortImpl* sortStrategy; // Current sorting strategy

public:
    Context(); // Constructor
    ~Context(); // Destructor
    void setStrategy(SortImpl*); // Set the sorting strategy
    void executeStrategy(Node*, map<string, double>) const; // Execute the current sorting strategy
};

// Doubly Linked List class
class DoublyLinkedList {
    friend class StockAccount;
private:
    Node* head; // Head of the list
    int size; // Size of the list
    Context* sortContext; // Sorting context
public:
    DoublyLinkedList(); // Constructor
    ~DoublyLinkedList(); // Destructor
    void setSortContext(Context*); // Set the sorting context
    Context* getSortContext() const; // Get the sorting context
    Node* getStock(const string&) const; // Get a stock node
    double getSumStockValue(map<string, double>) const; // Get the total value of stocks
    void addShares(const string&, int, map<string, double>); // Add shares
    void removeShares(const string&, int, map<string, double>); // Remove shares
    void deleteNode(const string&, map<string, double>); // Delete a node
    void displayList(map<string, double>) const; // Display the list
};

// Derived class StockAccount
class StockAccount : public Account {
    private:
        map<string, double> symbolMap; // Map of stock symbols to their price per share
        DoublyLinkedList *linkedList; // Doubly Linked list for the stocks
    public:
        StockAccount(); // Constructor
        virtual ~StockAccount(); // Destructor
        void initializeList(); // Initialize the stock list
        map<string, double> getSymbolMap(); // Get the symbol map
        void displayAccountOptions() const; // Display account options
        void displayStockPrice(); // Display stock price
        void displayStockPortfolio(); // Display stock portfolio
        void buyShares(BankAccount*, CurrentTime*); // Buy shares
        void sellShares(BankAccount*, CurrentTime*); // Sell shares
        void writeTransactionHistory(const string&, int, double, const string&, bool) const; // Write transaction history
        void plotGraph(); // Plot graph for the portfolio value
        void displayTransactionHistory() const; // Display transaction history
        void selectSortOption(); // Select stock list sorting option
};
#endif