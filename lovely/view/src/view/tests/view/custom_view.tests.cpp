#include <lovely/controller/tests/custom_controller.h>
#include <lovely/controller/tests/executor/simple.h>
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

    simple<custom_model> simple(model);

    custom_view view(model, simple);
}

TEST_CASE("custom view initialize with controller", "[model]")
{
    const bool bool_ref = true;
    const int int_ref = 42;

    custom_model model;
    model.initialize();

    custom_controller controller(model);

    custom_view view(model, controller);
}