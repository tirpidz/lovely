#include <lovely/controller/controller.h>
#include <lovely/controller/tests/custom_controller.h>
#include <lovely/controller/tests/executor/simple.h>
#include <lovely/controller/tests/updater/custom_updater.h>
#include <lovely/controller/updater/updater.h>
#include <lovely/model/model.h>
#include <lovely/model/registry/registry.h>
#include <lovely/model/tests/model/custom_model.h>
#include <lovely/model/tests/symbol/etf.h>
#include <lovely/model/tests/symbol/stock.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("controller initialize", "[controller]")
{
    const int int_ref = 42;

    custom_model model;
    model.initialize();

    controller<custom_model, custom_updater, simple<custom_model>> controller(model);

    int const* int_value_modified = nullptr;

    controller.update();
    model.cget("tse:td", int_value_modified);

    REQUIRE(*int_value_modified == int_ref + 10 + 1);

    controller.simple_math("tse:td", int_ref);
    model.cget("tse:td", int_value_modified);

    REQUIRE(*int_value_modified == int_ref + int_ref + 10 + 1);
}
