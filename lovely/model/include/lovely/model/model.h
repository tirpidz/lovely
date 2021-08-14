#pragma once

#include <lovely/model/exceptions.h>
#include <lovely/model/registry.h>

namespace lovely {

template <typename... types>
class model : public registry<types...> {
public:
    model() = default;
    virtual ~model() = default;

    model(const model& other) = delete;
    model& operator=(const model& other) = delete;

    void initialize()
    {
        if (_is_initialized) {
            throw exception::model::already_has_been_initialized();
        }

        initialize_internal();
        _is_initialized = true;
    }

    const bool is_initialized() const { return _is_initialized; }

protected:
    virtual void initialize_internal() {}

private:
    bool _is_initialized = {false};
};

}  // namespace lovely
