#pragma once

#include <cstdint>

namespace lovely {

class fetch final {
public:
    fetch();
    fetch(const fetch& other) = delete;
    fetch& operator=(const fetch& other) = delete;
    ~fetch() = default;

    int64_t number() const { return _number; }

private:
    int64_t _number;
};

}  // namespace lovely
