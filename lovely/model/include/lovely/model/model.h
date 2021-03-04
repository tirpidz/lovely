#pragma once

#include <lovely/model/exceptions.h>
#include <lovely/model/registry.h>

#include <functional>

namespace lovely {

template <typename... types>
class model final {
public:
    model() : _has_been_initialized(false) {}
    ~model() = default;

    model(const model& other) = delete;
    model& operator=(const model& other) = delete;

    void initialize(std::function<void(registry<types...>&)> callback)
    {
        if (_has_been_initialized) {
            throw exception::model::already_has_been_initialized();
        }

        _has_been_initialized = true;
        callback(_data);
    }

    const registry<types...>& data() { return _data; }

private:
    bool _has_been_initialized;
    registry<types...> _data;
};

}  // namespace lovely
