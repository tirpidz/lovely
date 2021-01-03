#include <lovely/window/window.h>

#include <catch.hpp>

TEST_CASE("Window number", "[window]") {
    lovely::window window;
    REQUIRE(window.number() == 43);
}
