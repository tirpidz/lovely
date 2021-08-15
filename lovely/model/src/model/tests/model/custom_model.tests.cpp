#include <lovely/model/tests/model/custom_model.h>
#include <lovely/model/tests/symbol/etf.h>
#include <lovely/model/tests/symbol/stock.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("custom model initialize", "[model]")
{
    const bool bool_ref = true;
    const int int_ref = 42;

    custom_model model;
    model.initialize();

    bool const* bool_value = nullptr;
    int* int_value = nullptr;

    model.cget("tse:td", bool_value);
    model.get("tse:td", int_value);

    REQUIRE(*bool_value == bool_ref);
    REQUIRE(*int_value == int_ref);
}