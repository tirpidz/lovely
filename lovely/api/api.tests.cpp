#include <lovely/api/api.h>

#include <catch.hpp>

TEST_CASE("Api number", "[api]") {
    lovely::api api;
    REQUIRE(api.number() == 41);
}
