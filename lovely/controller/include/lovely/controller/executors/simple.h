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
        int input = 0;
        _model.get(key, input);

        int output = 0;

        do_simple_math(output, input, increment);

        _model.set(key, output);
    }

protected:
    void do_simple_math(int& output, const int input, const int increment) { output = input + increment; }

private:
    model& _model;
};

}  // namespace lovely
