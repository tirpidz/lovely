#pragma once

namespace lovely {

class symbol {
public:
    symbol() {}
    symbol(const symbol& other) = delete;
    symbol& operator=(const symbol& other) = delete;
    ~symbol() = default;

    double market_value() const { return _market_value; }
    void set_market_value(const double market_value) { _market_value = market_value; }

private:
    double _market_value;
};

}  // namespace lovely
