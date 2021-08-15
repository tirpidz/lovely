#include <lovely/model/tests/model/custom_model.h>
#include <lovely/view/tests/view/custom_view.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("custom view initialize", "[model]")
{
    const bool bool_ref = true;
    const int int_ref = 42;

    custom_model model;
    model.initialize();

    custom_view view(model);
}