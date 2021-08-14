#include <lovely/model/model.h>
#include <lovely/model/tests/symbol/etf.h>
#include <lovely/model/tests/symbol/stock.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("model initialize", "[model]")
{
    const bool bool_ref = true;
    const int int_ref = 42;

    model<stock, etf, bool, int> model;
    REQUIRE(!model.is_initialized());
    model.initialize();
    REQUIRE(model.is_initialized());

    SECTION("throw when trying to initialize a second time") { REQUIRE_THROWS(model.initialize()); }
}
