#pragma once

#include <lovely/controller/exceptions.h>
#include <lovely/controller/executor/executor.h>

#include <type_traits>

namespace lovely {

template <typename model, typename updater, typename... executors>
class controller : public executors... {
public:
    controller(model& m) : executors(m)..., _updater(m)
    {
        if (!m.is_initialized()) {
            throw exception::controller::model_not_initialized();
        }

        if (!check<executor<model>, executors...>()) {
            throw exception::controller::base_class_not_executor();
        }
    }

    controller() = delete;
    virtual ~controller() = default;

    controller(const controller& other) = delete;
    controller& operator=(const controller& other) = delete;

    void update() { _updater.update(); }

protected:
    template <typename T, typename... Ts>
    constexpr bool check()
    {
        return std::conjunction_v<std::is_base_of<T, Ts>...>;
    }

    updater _updater;
};

}  // namespace lovely
