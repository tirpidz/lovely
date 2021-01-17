#include <lovely/model/registry.h>
#include <lovely/model/symbol/etf.h>
#include <lovely/model/symbol/stock.h>
#include <lovely/model/symbol/symbol.h>

#include <catch2/catch.hpp>
#include <string>
#include <utility>

using namespace lovely;

TEST_CASE("registry enroll", "[registry]")
{
    registry<stock, etf> registry;

    registry.enroll<stock>({"tse:td", "tse:rbc"});
    registry.enroll<etf>({"tse:vab"});

    const stock& td = registry.get<stock>("tse:td");
    const stock& rbc = registry.get<stock>("tse:rbc");
    const etf& vab = registry.get<etf>("tse:vab");
    auto s = registry.all<etf>();
    auto s2 = registry.all<stock>();

    REQUIRE(s.size() == 1);
    REQUIRE(s2.size() == 2);
}

TEST_CASE("registry enroll mistakes", "[registry]") {}
