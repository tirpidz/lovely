#pragma once

#include <lovely/controller/exceptions.h>
#include <lovely/controller/updater/updater.h>
#include <lovely/model/tests/model/custom_model.h>

namespace lovely {

class custom_updater : public updater<custom_model> {
public:
    custom_updater(custom_model& model) : updater<custom_model>(model)
    {
        if (!model.is_initialized()) {
            throw exception::controller::model_not_initialized();
        }
    }

protected:
    virtual void update_external_internal() override
    {
        int* int_value = nullptr;
        _model.get("tse:td", int_value);
        *int_value += 1;
    }

    virtual void update_derived_internal() override
    {
        int* int_value = nullptr;
        _model.get("tse:td", int_value);
        *int_value += 10;
    }
};
}  // namespace lovely