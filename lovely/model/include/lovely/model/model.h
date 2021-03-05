#pragma once

#include <lovely/model/exceptions.h>
#include <lovely/model/registry.h>

#include <functional>

namespace lovely {

template <typename... types>
class model final {
public:
    model(std::function<void(registry<types...>&)> initialize_callback)
        : _initialize_callback(initialize_callback)
        , _has_been_initialized(false)
    {
        if (_initialize_callback == nullptr) {
            throw exception::model::callback_cannot_be_null();
        }
    }

    model() = delete;
    ~model() = default;

    model(const model& other) = delete;
    model& operator=(const model& other) = delete;

    void initialize()
    {
        if (_has_been_initialized) {
            throw exception::model::already_has_been_initialized();
        }

        _has_been_initialized = true;
        _initialize_callback(_data);
    }

    const registry<types...>& data() { return _data; }

private:
    std::function<void(registry<types...>&)> _initialize_callback;
    bool _has_been_initialized;
    registry<types...> _data;
};

}  // namespace lovely
