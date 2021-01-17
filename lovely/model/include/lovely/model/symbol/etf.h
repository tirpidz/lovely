#pragma once

#include <lovely/model/symbol/symbol.h>

namespace lovely {

class etf final : public symbol {
public:
    etf() {}
    etf(const etf& other) = delete;
    etf& operator=(const etf& other) = delete;
    ~etf() = default;
};

}  // namespace lovely
