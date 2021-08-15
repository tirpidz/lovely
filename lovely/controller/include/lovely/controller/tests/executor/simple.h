#pragma once

#include <lovely/controller/exceptions.h>
#include <lovely/controller/executor/executor.h>

#include <string>

namespace lovely {

template <typename model>
class simple : public executor<model> {
public:
    simple(model& m) : executor<model>(m) {}
    virtual ~simple() = default;

    void simple_math(const std::string& key, const int increment)
    {
        int* value = nullptr;
        this->_model.get(key, value);

        do_simple_math(*value, increment);
    }

protected:
    void do_simple_math(int& value, const int increment) { value += increment; }
};

}  // namespace lovely
