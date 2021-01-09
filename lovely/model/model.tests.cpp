#include <lovely/model/model.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("model number", "[model]") {
    model::model model;
    REQUIRE(model.number() == 41);
}
