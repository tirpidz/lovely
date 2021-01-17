#include <lovely/model/registry.h>
#include <lovely/model/symbol/etf.h>
#include <lovely/model/symbol/stock.h>

#include <catch2/catch.hpp>
#include <string>
#include <vector>

using namespace lovely;

TEST_CASE("registry enroll", "[registry]")
{
    registry<stock, etf> registry;

    registry.enroll<stock>({"tse:td", "tse:rbc"});
    registry.enroll<etf>({"tse:vab"});

    const stock& td = registry.get<stock>("tse:td");
    const stock& rbc = registry.get<stock>("tse:rbc");
    const etf& vab = registry.get<etf>("tse:vab");
    const std::vector<etf const*>& s = registry.all<etf>();
    const std::vector<stock const*>& s2 = registry.all<stock>();

    REQUIRE(s.size() == 1);
    REQUIRE(s2.size() == 2);
}

TEST_CASE("registry enroll mistakes", "[registry]")
{
    registry<stock, etf> registry;

    registry.enroll<stock>({"tse:td", "tse:rbc"});
    registry.enroll<etf>({"tse:vab"});

    REQUIRE_THROWS_WITH(registry.enroll<stock>({"tse:td"}), "key is already enrolled");

    REQUIRE_THROWS_WITH(registry.get<stock>({"tse:not-found"}), "key is not found");
}
