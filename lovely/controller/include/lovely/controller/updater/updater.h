#pragma once

#include <lovely/controller/exceptions.h>
#include <lovely/model/model.h>

namespace lovely {

template <typename model>
class updater {
public:
    updater(model& m) : _model(m)
    {
        if (!m.is_initialized()) {
            throw exception::controller::model_not_initialized();
        }
    }

    updater() = delete;
    virtual ~updater() = default;

    updater(const updater& other) = delete;
    updater& operator=(const updater& other) = delete;

    void update()
    {
        update_external();
        update_derived();
    }

protected:
    void update_external() { update_external_internal(); }
    void update_derived() { update_derived_internal(); }

    virtual void update_external_internal() {}
    virtual void update_derived_internal() {}

    model& _model;
};

}  // namespace lovely
