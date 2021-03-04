#pragma once

#include <cstdint>

namespace lovely {
namespace view {

class view final {
public:
    view();
    ~view() = default;

    view(const view& other) = delete;
    view& operator=(const view& other) = delete;

    int64_t number() const { return _number; }

private:
    int64_t _number;
};

}  // namespace view
}  // namespace lovely
