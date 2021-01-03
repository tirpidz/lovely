#pragma once

#include <cstdint>

namespace lovely {

class window final {
public:
    window();
    window(const window& other) = delete;
    window& operator=(const window& other) = delete;
    ~window() = default;

    int64_t number() const { return _number; }

private:
    int64_t _number;
};

}  // namespace lovely
