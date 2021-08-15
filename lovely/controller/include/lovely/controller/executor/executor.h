#pragma once

#include <lovely/controller/exceptions.h>

#include <string>

namespace lovely {

template <typename model>
class executor {
public:
    executor(model& m) : _model(m)
    {
        if (!m.is_initialized()) {
            throw exception::controller::model_not_initialized();
        }
    }

    executor() = delete;
    virtual ~executor() = default;

    executor(const executor& other) = delete;
    executor& operator=(const executor& other) = delete;

protected:
    model& _model;
};

}  // namespace lovely
