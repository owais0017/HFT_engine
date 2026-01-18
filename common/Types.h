#ifndef TYPES_H
#define TYPES_H

#include <iostream>
#include <cstdint>
#include <cstring>

using namespace std;

//This code defines a type-safe, scoped enum named Side, stored in 1 byte, with two possible values: BUY and SELL
enum class Side : uint8_t {
    BUY = 0,
    SELL = 1
};

// 2. Enum for Order Type (Limit is standard for HFT)
enum class OrderType : uint8_t {
    LIMIT = 0,
    MARKET = 1
};

// 3. The Core Order Structure
// We use 'pragma pack' to ensure no extra padding bytes are added by the compiler.
// This makes the struct as small as possible for the CPU cache.
#pragma pack(push, 1)
struct Order {
    uint64_t id;          // Unique Order ID
    uint64_t px;          // Price (stored as long to avoid floating point issues)
    uint32_t qty;         // Quantity
    Side side;            // Buy or Sell
    char sym[8];          // Ticker symbol (e.g., "AAPL") - no std::string!

    // Helper to set symbol safely
    void setSym(const char* s) {
        strncpy(sym, s, sizeof(sym));
    }
};

// 4. Execution Report (Sent when a trade happens)
struct ExecutionReport {
    uint64_t tradeId;     // Unique Trade ID
    uint64_t orderId;     // The original Order ID
    uint64_t fillPx;      // Price at which it was filled
    uint32_t fillQty;     // Quantity filled
    char sym[8];
};
#pragma pack(pop)

#endif