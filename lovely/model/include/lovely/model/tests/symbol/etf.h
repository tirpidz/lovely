#pragma once

#include <lovely/model/tests/symbol/symbol.h>

namespace lovely {

class etf final : public symbol {
public:
    etf() {}
    virtual ~etf() = default;

    etf(const etf& other) = default;
    etf& operator=(const etf& other) = default;
};

}  // namespace lovely
