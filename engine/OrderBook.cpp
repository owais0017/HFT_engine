#include "OrderBook.h"

vector<ExecutionReport> OrderBook::addOrder(Order order) {
    vector<ExecutionReport> trades;

    if (order.side == Side::BUY) {
        // Try to match against the 'asks' (Sellers)
        auto it = asks.begin();
        while (it != asks.end() && order.qty > 0 && it->first <= order.px) {
            auto& priceLevel = it->second;
            auto lit = priceLevel.begin();

            while (lit != priceLevel.end() && order.qty > 0) {
                uint32_t tradedQty = min(order.qty, lit->qty);
                
                // Create a trade report
                trades.push_back({123, lit->id, it->first, tradedQty}); // Simplified ID
                
                order.qty -= tradedQty;
                lit->qty -= tradedQty;

                if (lit->qty == 0) {
                    lit = priceLevel.erase(lit);
                } else {
                    ++lit;
                }
            }
            if (priceLevel.empty()) {
                it = asks.erase(it);
            } else {
                ++it;
            }
        }
        // If still have quantity, add to bids (the book)
        if (order.qty > 0) bids[order.px].push_back(order);

    } else {
        // SELL logic (Mirror of BUY logic - matching against bids)
        auto it = bids.begin();
        while (it != bids.end() && order.qty > 0 && it->first >= order.px) {
            auto& priceLevel = it->second;
            auto lit = priceLevel.begin();
            while (lit != priceLevel.end() && order.qty > 0) {
                uint32_t tradedQty = min(order.qty, lit->qty);
                trades.push_back({456, lit->id, it->first, tradedQty});
                order.qty -= tradedQty;
                lit->qty -= tradedQty;
                lit = (lit->qty == 0) ? priceLevel.erase(lit) : ++lit;
            }
            it = (priceLevel.empty()) ? bids.erase(it) : ++it;
        }
        if (order.qty > 0) asks[order.px].push_back(order);
    }
    return trades;
}