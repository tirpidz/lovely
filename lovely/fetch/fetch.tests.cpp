#include <lovely/fetch/fetch.h>

#include <catch.hpp>

TEST_CASE("Fetch number", "[fetch]") {
    lovely::fetch fetch;
    REQUIRE(fetch.number() == 42);
}
