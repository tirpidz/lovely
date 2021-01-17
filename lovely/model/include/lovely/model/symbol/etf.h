#pragma once

#include <lovely/model/symbol/symbol.h>

namespace lovely {

class etf final : public symbol {
public:
    etf() {}
    etf(const etf& other) = default;
    etf& operator=(const etf& other) = default;
    ~etf() = default;
};

}  // namespace lovely
