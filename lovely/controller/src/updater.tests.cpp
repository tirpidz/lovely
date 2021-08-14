#include <lovely/controller/tests/updater/custom_updater.h>
#include <lovely/controller/updater.h>
#include <lovely/model/model.h>
#include <lovely/model/registry.h>
#include <lovely/model/tests/model/custom_model.h>
#include <lovely/model/tests/symbol/etf.h>
#include <lovely/model/tests/symbol/stock.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("updater initialize", "[controller]")
{
    const int int_ref = 42;

    custom_model model;
    model.initialize();

    custom_updater updater(model);

    int const* int_value_modified = nullptr;

    updater.update();
    model.cget("tse:td", int_value_modified);

    REQUIRE(*int_value_modified == int_ref + 10 + 1);
}
