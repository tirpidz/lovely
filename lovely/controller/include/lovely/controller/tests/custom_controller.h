#pragma once

#include <lovely/controller/controller.h>
#include <lovely/controller/exceptions.h>
#include <lovely/controller/tests/executor/simple.h>
#include <lovely/controller/tests/updater/custom_updater.h>
#include <lovely/model/tests/model/custom_model.h>

namespace lovely {

class custom_controller final : public controller<custom_model, custom_updater, simple<custom_model>> {
public:
    custom_controller(custom_model& m) : controller(m)
    {
        if (!m.is_initialized()) {
            throw exception::controller::model_not_initialized();
        }
    }

    virtual ~custom_controller() = default;

    custom_controller(const custom_controller& other) = delete;
    custom_controller& operator=(const custom_controller& other) = delete;
};

}  // namespace lovely