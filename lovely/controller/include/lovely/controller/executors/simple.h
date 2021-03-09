#pragma once

#include <lovely/model/model.h>

#include <string>

namespace lovely {

template <typename model>
class simple {
public:
    simple(model& m) : _model(m) {}

    simple() = delete;
    virtual ~simple() = default;

    simple(const simple& other) = delete;
    simple& operator=(const simple& other) = delete;

    void simple_math(const std::string& key, const int increment)
    {
        int value = 0;
        _model.get(key, value);

        do_simple_math(value, increment);

        _model.set(key, value);
    }

protected:
    void do_simple_math(int& value, const int increment) { value += increment; }

private:
    model& _model;
};

}  // namespace lovely
