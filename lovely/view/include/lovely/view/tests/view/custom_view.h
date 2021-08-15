#pragma once

#include <lovely/controller/tests/executor/simple.h>
#include <lovely/model/tests/model/custom_model.h>
#include <lovely/view/view.h>

#include <string>

namespace lovely {

class custom_view final : public view<custom_model> {
public:
    custom_view(custom_model& m, simple<custom_model>& simple) : view<custom_model>(m), _simple(simple) {}
    virtual ~custom_view() = default;

protected:
    simple<custom_model>& _simple;
};

}  // namespace lovely
