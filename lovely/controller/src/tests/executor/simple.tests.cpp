#include <lovely/controller/tests/executor/simple.h>
#include <lovely/model/model.h>
#include <lovely/model/registry.h>
#include <lovely/model/tests/model/custom_model.h>
#include <lovely/model/tests/symbol/etf.h>
#include <lovely/model/tests/symbol/stock.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("simple initialize", "[controller]")
{
    const int int_ref = 42;

    custom_model model;
    model.initialize();

    simple<custom_model> executor(model);

    int const* int_value_modified = nullptr;
    executor.simple_math("tse:td", int_ref);
    model.cget("tse:td", int_value_modified);

    REQUIRE(*int_value_modified == int_ref + int_ref);
}
