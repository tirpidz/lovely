#pragma once

#include <lovely/model/symbol/symbol.h>

namespace lovely {

class stock final : public symbol {
public:
    stock() {}
    stock(const stock& other) = default;
    stock& operator=(const stock& other) = default;
    ~stock() = default;
};

}  // namespace lovely
