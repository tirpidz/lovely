#pragma once

#include <lovely/controller/controller.h>
#include <lovely/controller/tests/executor/simple.h>
#include <lovely/controller/tests/updater/custom_updater.h>
#include <lovely/model/tests/model/custom_model.h>

namespace lovely {

class custom_controller : public controller<custom_model, custom_updater, simple<custom_model>> {
public:
    custom_controller(custom_model& m) : controller(m) {}

    custom_controller() = delete;
    virtual ~custom_controller() = default;

    custom_controller(const custom_controller& other) = delete;
    custom_controller& operator=(const custom_controller& other) = delete;
};

}  // namespace lovely