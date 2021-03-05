#pragma once

#include <lovely/controller/exceptions.h>
#include <lovely/model/model.h>

#include <cstdint>
#include <functional>

namespace lovely {

template <typename... types>
class controller final {
public:
    controller(model<types...>& model, std::function<void(lovely::model<types...>&)> update_external_callback,
               std::function<void(lovely::model<types...>&)> update_derived_callback)
        : _model(model)
        , _update_external_callback(update_external_callback)
        , _update_derived_callback(update_derived_callback)
    {
        if (!model.is_initialized()) {
            throw exception::controller::model_is_not_initialized();
        }

        if (_update_external_callback == nullptr) {
            throw exception::controller::callback_cannot_be_null();
        }

        if (_update_derived_callback == nullptr) {
            throw exception::controller::callback_cannot_be_null();
        }
    }

    controller() = delete;
    ~controller() = default;

    controller(const controller& other) = delete;
    controller& operator=(const controller& other) = delete;

    void update_external() { _update_external_callback(_model); }
    void update_derived() { _update_derived_callback(_model); }

private:
    model<types...>& _model;

    std::function<void(model<types...>&)> _update_external_callback;
    std::function<void(model<types...>&)> _update_derived_callback;
};

}  // namespace lovely
