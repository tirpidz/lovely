#pragma once

#include <cstdint>

namespace lovely {

class api final {
public:
    api();
    api(const api& other) = delete;
    api& operator=(const api& other) = delete;
    ~api() = default;

    int64_t number() const { return _number; }

private:
    int64_t _number;
};

}  // namespace lovely
