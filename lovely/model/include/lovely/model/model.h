#pragma once

#include <cstdint>

namespace lovely {
namespace model {

class model final {
public:
    model();
    model(const model& other) = delete;
    model& operator=(const model& other) = delete;
    ~model() = default;

    int64_t number() const { return _number; }

private:
    int64_t _number;
};

}  // namespace model
}  // namespace lovely
