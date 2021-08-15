#pragma once

#include <lovely/view/exceptions.h>

namespace lovely {

template <typename model>
class view {
public:
    view(model& m) : _model(m)
    {
        if (!m.is_initialized()) {
            throw exception::view::model_not_initialized();
        }
    }
    view() = delete;
    virtual ~view() = default;

    view(const view& other) = delete;
    view& operator=(const view& other) = delete;

    void draw() { draw_internal(); }

protected:
    virtual void draw_internal() {}

private:
    const model& _model;
};

}  // namespace lovely
