#include <lovely/view/view.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("view number", "[view]")
{
    view view;
    REQUIRE(view.number() == 43);
}
