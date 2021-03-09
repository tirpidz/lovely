#pragma once

#include <lovely/controller/exceptions.h>

#include <cstdint>
#include <functional>

namespace lovely {

template <typename... types>
class updater final {
public:
    updater(model<types...>& model, std::function<void(lovely::model<types...>&)> update_external_callback,
            std::function<void(lovely::model<types...>&)> update_derived_callback)
        : _model(model)
        , _update_external_callback(update_external_callback)
        , _update_derived_callback(update_derived_callback)
    {
        if (_update_external_callback == nullptr) {
            throw exception::controller::callback_cannot_be_null();
        }

        if (_update_derived_callback == nullptr) {
            throw exception::controller::callback_cannot_be_null();
        }
    }

    updater() = delete;
    ~updater() = default;

    updater(const updater& other) = delete;
    updater& operator=(const updater& other) = delete;

    void update()
    {
        update_external();
        update_derived();
    }

protected:
    void update_external() { _update_external_callback(_model); }
    void update_derived() { _update_derived_callback(_model); }

    model<types...>& _model;

    std::function<void(model<types...>&)> _update_external_callback;
    std::function<void(model<types...>&)> _update_derived_callback;
};

}  // namespace lovely
