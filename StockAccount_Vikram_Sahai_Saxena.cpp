#include "StockAccount_Vikram_Sahai_Saxena.h"

// Node class constructor
Node::Node(string symbol, int shares) : symbol(symbol), shares(shares), next(nullptr), prev(nullptr) {}

// Get the number of shares
int Node::getShares() const { return shares; }

// Swap two nodes in the doubly linked list
void Node::swapNodes(Node** head, Node* first, Node* second) {
    if (first->next) {
        first->prev->next = second;
    }
    if (second->next) {
        second->next->prev = first;
    }
    first->next = second->next;
    second->prev = first->prev;
    second->next = first;
    first->prev = second;

    if (*head == first) {
        *head = second;
    }
}

// Destructor for SortImpl
SortImpl::~SortImpl() {}

// Destructor for SortBubble
SortBubble::~SortBubble() {}

// Sorting Nodes using Bubble Sort
void SortBubble::sort(Node* head, map<string, double> pricePerShareMap) const {
    bool swapped;
    do {
        swapped = false;
        Node* current = head;
        while (current->next) {
            if (current->shares * pricePerShareMap[current->symbol] < current->next->shares * pricePerShareMap[current->next->symbol]) {
                Node::swapNodes(&head, current, current->next);
                swapped = true;
                continue;
            }
            current = current->next;
        }
    } while (swapped);
}

// Destructor for SortSelection
SortSelection::~SortSelection() {}

// Sorting Nodes using Selection Sort
void SortSelection::sort(Node* head, map<string, double> pricePerShareMap) const {
    Node *i, *j, *max;
    for (i = head; i != nullptr && i->next != nullptr; i = i->next) {
        max = i;
        for (j = i->next; j != nullptr; j = j->next) {
            if (j->shares * pricePerShareMap[j->symbol] > max->shares * pricePerShareMap[max->symbol]) {
                max = j;
            }
        }
        if (max != i) {
            Node::swapNodes(&head, i, max);
        }
    }
}

// Context constructor
Context::Context() : sortStrategy(new SortBubble()) {}

// Context destructor
Context::~Context() { delete sortStrategy; }

// Set the sorting strategy
void Context::setStrategy(SortImpl* sortStrategy) {
    this->sortStrategy = sortStrategy;
}

// Execute the current sorting strategy
void Context::executeStrategy(Node* head, map<string, double> pricePerShareMap) const {
    if (this->sortStrategy) {
        this->sortStrategy->sort(head, pricePerShareMap);
    }
}

// DoublyLinkedList constructor
DoublyLinkedList::DoublyLinkedList() : head(nullptr), size(0), sortContext(new Context()) {}

// DoublyLinkedList destructor
DoublyLinkedList::~DoublyLinkedList() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    delete getSortContext();
}

// Set the sorting context
void DoublyLinkedList::setSortContext(Context* sortContext) { this->sortContext = sortContext; }

// Get the sorting context
Context* DoublyLinkedList::getSortContext() const { return sortContext; }

// Get a specific stock from the list
Node* DoublyLinkedList::getStock(const string& symbol) const {
    Node* temp = head;
    while (temp) {
        if (symbol == temp->symbol) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Get the total value of all stocks in the list
double DoublyLinkedList::getSumStockValue(map<string, double> pricePerShareMap) const {
    double sum = 0;
    Node* temp = head;
    while (temp) {
        sum += temp->shares * pricePerShareMap[temp->symbol];
        temp = temp->next;
    }
    return sum;
}

// Add shares to the list
void DoublyLinkedList::addShares(const string& symbol, int shares, map<string, double> pricePerShareMap) {

    if (getStock(symbol)) {
        getStock(symbol)->shares += shares;
        return;
    }

    Node* newNode = new Node(symbol, shares);
    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }

    size++;

    //sort
    getSortContext()->executeStrategy(head, pricePerShareMap);
}

// Remove shares from the list
void DoublyLinkedList::removeShares(const string& symbol, int shares, map<string, double> pricePerShareMap) {
        if (getStock(symbol)) {
        getStock(symbol)->shares -= shares;
        if (0 < getStock(symbol)->shares) {
            return;
        }
        deleteNode(symbol, pricePerShareMap);
    }
}

// Delete a node from the list
void DoublyLinkedList::deleteNode(const string& symbol, map<string, double> pricePerShareMap) {
    Node* temp = head;
    if (temp && symbol == temp->symbol) {
        head = temp->next;
        if (head) {
            head->prev = nullptr;
        }
        delete temp;
        return;
    }
    while (temp && symbol != temp->symbol) {
        temp = temp->next;
    }
    if (!temp) {
        return;
    }
    if (temp->next) {
        temp->next->prev = temp->prev;
    }
    if (temp->prev) {
        temp->prev->next = temp->next;
    }
    delete temp;

    size--;

    //sort
    getSortContext()->executeStrategy(head, pricePerShareMap);
}

// Display the list of stocks
void DoublyLinkedList::displayList(map<string, double> pricePerShareMap) const {
    //sort
    if (0 < size) {
        getSortContext()->executeStrategy(head, pricePerShareMap);
    }
    
    Node* temp = head;
    while (temp) {
        cout << left << setw(20) << temp->symbol << left << setw(20) <<temp->shares << "$" << left << setw(19) << fixed << setprecision(2) << pricePerShareMap[temp->symbol] << "$" << left << setw(19) << temp->shares * pricePerShareMap[temp->symbol] << endl ;
        temp = temp->next;
    }
}

// StockAccount constructor
StockAccount::StockAccount() : linkedList(new DoublyLinkedList()) { initializeList(); }

// StockAccount destructor
StockAccount::~StockAccount() {
    CurrentTime* currentTime = CurrentTime::getInstance();  
    ofstream file;
    file.open("portfolio_history.txt", fstream::app);
    file << left << setw(20) << getCashBalance() + linkedList->getSumStockValue(getSymbolMap()) << left << setw(20) << getCashBalance() << left << setw(20)  << currentTime->getCurrentTime();
    file.close();
    delete linkedList;
}

// Initialize the stock list from the history file
void StockAccount::initializeList() {
    ifstream file("stock_transaction_history.txt");
    string line, buyOrSell, symbol, shares;
    while (getline(file, line)) {
        stringstream ss(line);
        ss >> buyOrSell >> symbol >> shares;
        if ("Buy" == buyOrSell) {
            linkedList->addShares(symbol, stoi(shares), getSymbolMap());
        } else {
            linkedList->removeShares(symbol, stoi(shares), getSymbolMap());
        }
    }
}

// Get the map of stock symbols and their price per share
map<string, double> StockAccount::getSymbolMap() {
    srand(time(0)); // Seed for random number generation
    int fileChoice = rand() % 2; // Randomly choose 0 or 1

    string fileName = (0 == fileChoice) ? "Result_1.txt" : "Result_2.txt";
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Failed to open " << fileName << endl;
        return symbolMap;
    }

    string line, companySymbol, pricePerShare;
    while (getline(file, line)) {
        stringstream ss(line);
        ss >> companySymbol >> pricePerShare;
        symbolMap[companySymbol] = stod(pricePerShare);
    }
    file.close();
    return symbolMap;
}

// Display account options
void StockAccount::displayAccountOptions() const {
    cout << "Please select an option:" << endl;
    cout << "1. Display the price for a stock symbol" << endl;
    cout << "2. Display the current portfolio" << endl;
    cout << "3. Buy shares" << endl;
    cout << "4. Sell shares" << endl;
    cout << "5. View a graph for the portfolio value" << endl; 
    cout << "6. View transaction history" << endl;
    cout << "7. Select sorting method" << endl;
    cout << "8. Return to previous menu" << endl << endl;
}

// Display the current stock price
void StockAccount::displayStockPrice() {
    cout << "Please enter the stock symbol: ";
    string symbol;
    cin >> symbol;
    map<string, double> pricePerShareMap = getSymbolMap();
    if (0 == pricePerShareMap.count(symbol)) {
        cout << "The symbol cannot be found." << endl;
    } else {
        cout << left << setw(20) << "Company Symbol" << left << setw(20) << "Price per share" << endl;
        cout << left << setw(20) << symbol << "$" << left << setw(19) << pricePerShareMap[symbol] << endl << endl;
    }
}

// Display the stock portfolio
void StockAccount::displayStockPortfolio() {
    cout << "Cash Balance = $" << getCashBalance() << endl;
    cout << left << setw(20) << "Company-Symbol" << left << setw(20) << "Number" << left << setw(20) << "Price-per-share" << left << setw(20) << "Total value" << endl;
    linkedList->displayList(getSymbolMap());
    cout << "Total portfolio value: $" << fixed << setprecision(2) << getCashBalance() + linkedList->getSumStockValue(getSymbolMap()) << endl << endl;
}

// Buy shares
void StockAccount::buyShares(BankAccount* bankAccount, CurrentTime* currentTime) {
    cout << "Please enter the stock symbol you wish to purchase: ";
    string symbol;
    cin >> symbol;
    map<string, double> pricePerShareMap = getSymbolMap();
    if (0 == pricePerShareMap.count(symbol)) {
        cout << "The symbol cannot be found." << endl;
        return;
    }
    cout << "Please enter the number of shares: ";
    int shares;
    cin >> shares;
    if (0 >= shares) {
        cout << "Please enter a number greater than zero." << endl << endl;
        return;
    }
    cout << "Please enter the maximum amount you are willing to pay per share: ";
    double limit;
    cin >> limit;
    if (0 >= limit) {
        cout << "Please enter an amount greater than zero." << endl << endl;
        return;
    }
    if (limit < pricePerShareMap[symbol]) {
        cout << "Cost per stock is higher than the amount you are willing to pay." << endl << endl;
        return;
    }
    if (bankAccount->getCashBalance() < (shares * limit)) {
        cout << "You have entered a stock purchase amount that is more than your current cash balance in bank account." << endl << endl;
        return;
    }

    //buy share
    linkedList->addShares(symbol, shares, pricePerShareMap);
    bankAccount->debit(shares * limit);
    cout << "You have purchased " << shares << " shares of " << symbol << " at $" << limit << " each for a total of $" 
    << fixed << setprecision(2) << shares * limit << endl << endl;
    
    //write to stock_transaction_history.txt
    writeTransactionHistory(symbol, shares, limit, currentTime->getCurrentHHMMSS(), true);
    
    //write to bank_transaction_history.txt
    bankAccount->writeTransactionHistory(symbol, shares, limit, currentTime->getCurrentMMDDYYYY(), true);
}

// Sell shares
void StockAccount::sellShares(BankAccount* bankAccount, CurrentTime* currentTime) {
    cout << "Please enter the stock symbol you wish to sell: ";
    string symbol;
    cin >> symbol;
    if (!linkedList->getStock(symbol)) {
        cout << "You have entered a stock that is not in your portfolio." << endl << endl;
        return;
    }
    cout << "Please enter the number of shares: ";
    int shares;
    cin >> shares;
    if (0 >= shares) {
        cout << "Please enter a number greater than zero." << endl << endl;
        return;
    }
    if (shares > linkedList->getStock(symbol)->getShares()) {
        cout << "Insufficient shares in your portfolio" << endl << endl;
        return;
    }
    cout << "Please enter the minimum amount you want to sell each share of the stock for: ";
    double limit;
    cin >> limit;
    if (0 >= limit) {
        cout << "Please enter an amount greater than zero." << endl << endl;
        return;
    }
    map<string, double> pricePerShareMap = getSymbolMap();
    if (limit > pricePerShareMap[symbol]) {
        cout << "Price per stock is lower than the amount you are willing to sell for." << endl << endl;
        return;
    }
    linkedList->removeShares(symbol, shares, pricePerShareMap);
    bankAccount->credit(shares * limit);

    cout << "You have sold " << shares << " shares of " << symbol << " at $" << limit << " each for a total of $" 
    << shares * limit << "." << endl << endl;

    //write to stock_transaction_history.txt
    writeTransactionHistory(symbol, shares, limit, currentTime->getCurrentHHMMSS(), false);
    
    //write to bank_transaction_history.txt
    bankAccount->writeTransactionHistory(symbol, shares, limit, currentTime->getCurrentMMDDYYYY(), false);

}

// Write transaction history
void StockAccount::writeTransactionHistory(const string& symbol, int shares, double pricePerShare, const string& time, bool isBuy) const{
    ofstream file;
    file.open("stock_transaction_history.txt", fstream::app);
    string buyOrSell = (isBuy) ? "Buy" : "Sell" ;
    file << left << setw(20) << buyOrSell << left << setw(20) << symbol << left << setw(20) << shares << "$" << left << setw(19) << fixed << setprecision(2) << pricePerShare << "$" << left << setw(19) << shares * pricePerShare << left << setw(20) << time << endl;
    file.close();
}

// Plot graph for the change in portfolio value over time
void StockAccount::plotGraph() {
    system("Rscript plotGraph.R portfolio_history.txt");
    cout << endl;
}

// Display transaction history
void StockAccount::displayTransactionHistory() const {
    ifstream file("stock_transaction_history.txt");

    if (!file.is_open()) {
        cerr << "Failed to open stock_transaction_history.txt" << endl;
        return;
    }
    cout << left << setw(20) << "Event" << left << setw(20) <<  "CompSymbol" << left << setw(20) << "Number" << left << setw(20) << "PricePerShare" << left << setw(20) << "TotalValue" << left << setw(20) << "Time" << endl;
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
    cout << endl;
}

// Select sorting option to sort the stock list using Strategy Design Pattern
void StockAccount::selectSortOption() {
    cout << "Please enter the sorting option for portfolio (1 - Bubble, 2 - Selection): " << endl;
    int sortOption;
    cin >> sortOption;
    switch (sortOption) {
        case 1:
            {
                linkedList->setSortContext(linkedList->getSortContext());
                cout << "Bubble Sort selected." << endl << endl;
                break;
            }
        case 2:
            {
                linkedList->getSortContext()->setStrategy(new SortSelection());
                linkedList->setSortContext(linkedList->getSortContext());
                cout << "Selection Sort selected." << endl << endl;
                break;
            }
        default:
            cout << "Option is not valid!" << endl;
    }
}