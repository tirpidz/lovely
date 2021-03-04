#pragma once

#include <cstdint>

namespace lovely {
namespace controller {

class controller final {
public:
    controller();
    ~controller() = default;

    controller(const controller& other) = delete;
    controller& operator=(const controller& other) = delete;

    int64_t number() const { return _number; }

private:
    int64_t _number;
};

}  // namespace controller
}  // namespace lovely
