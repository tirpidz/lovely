#pragma once

#include <lovely/model/exceptions.h>
#include <lovely/model/registry.h>

#include <functional>

namespace lovely {

template <typename... types>
class model final : public registry<types...> {
public:
    model(std::function<void(registry<types...>&)> initialize_callback)
        : _initialize_callback(initialize_callback)
        , _is_initialized(false)
    {
        if (_initialize_callback == nullptr) {
            throw exception::model::callback_cannot_be_null();
        }
    }

    model() = delete;
    virtual ~model() = default;

    model(const model& other) = delete;
    model& operator=(const model& other) = delete;

    void initialize()
    {
        if (_is_initialized) {
            throw exception::model::already_has_been_initialized();
        }

        _is_initialized = true;
        _initialize_callback(*this);
    }

    const bool is_initialized() const { return _is_initialized; }

private:
    std::function<void(registry<types...>&)> _initialize_callback;
    bool _is_initialized;
};

}  // namespace lovely
