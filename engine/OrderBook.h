#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "../common/Types.h"
#include <map>
#include <list>
#include <vector>

using namespace std;

class OrderBook {
private:
    // A 'PriceLevel' is just a list of orders waiting at that price
    using PriceLevel = list<Order>;

    // The Book: Maps price to a list of orders
    // map is sorted: Buy side needs descending, Sell side needs ascending
    map<uint64_t, PriceLevel, greater<uint64_t>> bids; // Highest buy price first
    map<uint64_t, PriceLevel, less<uint64_t>> asks;    // Lowest sell price first

    string symbol;

public:
    OrderBook(string sym) : symbol(sym) {}

    // The core function: takes an order, returns trades (ExecutionReports)
    vector<ExecutionReport> addOrder(Order order);
    
    // For later: cancel logic
    void cancelOrder(uint64_t orderId);
};

#endif