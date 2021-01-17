#pragma once

#include <lovely/model/symbol/symbol.h>

namespace lovely {

class stock final : public symbol {
public:
    stock() {}
    stock(const stock& other) = delete;
    stock& operator=(const stock& other) = delete;
    ~stock() = default;
};

}  // namespace lovely
