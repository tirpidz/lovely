#include <lovely/controller/controller.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("controller number", "[controller]")
{
    controller::controller controller;
    REQUIRE(controller.number() == 41);
}
