#pragma once

namespace lovely {

template <typename model, typename updater, typename... executor>
class controller : public executor... {
public:
    controller(model& m) : executor(m)..., _updater(m) {}

    controller() = delete;
    virtual ~controller() = default;

    controller(const controller& other) = delete;
    controller& operator=(const controller& other) = delete;

    void update() { _updater.update(); }

protected:
    updater _updater;
};

}  // namespace lovely
