#pragma once

#include <lovely/model/tests/model/custom_model.h>
#include <lovely/view/view.h>

#include <string>

namespace lovely {

class custom_view final : public view<custom_model> {
public:
    custom_view(custom_model& m) : view<custom_model>(m) {}
    virtual ~custom_view() = default;
};

}  // namespace lovely
