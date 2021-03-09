#pragma once

#include <cstdint>
#include <functional>

namespace lovely {

template <typename model, typename updater, typename... executors>
class controller final : public executors... {
public:
    controller(model& m, updater& u) : executors(m)..., _updater(u) {}

    controller() = delete;
    virtual ~controller() = default;

    controller(const controller& other) = delete;
    controller& operator=(const controller& other) = delete;

    void update() { _updater.update(); }

protected:
    updater& _updater;
};

}  // namespace lovely
