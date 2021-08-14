#pragma once

#include <cstdint>

namespace lovely {

template <typename model, typename controller>
class view {
public:
    view(const model& m, controller& c) : _model(m), _controller(c) {}
    view() = delete;
    virtual ~view() = default;

    view(const view& other) = delete;
    view& operator=(const view& other) = delete;

    void update()
    {
        _controller.update();
        update_internal();
    }

protected:
    virtual void update_internal();

private:
    const model& _model;
    controller _controller;
};

}  // namespace lovely
