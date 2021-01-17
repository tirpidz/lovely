#include <lovely/model/registry.h>
#include <lovely/model/symbol/etf.h>
#include <lovely/model/symbol/stock.h>

#include <catch2/catch.hpp>
#include <string>
#include <tuple>
#include <vector>

using namespace lovely;

TEST_CASE("registry enroll", "[registry]")
{
    registry<stock, etf, bool> registry;

    registry.enroll<stock>({"tse:td", "tse:rbc"});
    registry.enroll<etf>({"tse:vab"});
    registry.enroll<bool>({"tse:td"});

    const stock& td = registry.single<stock>("tse:td");
    const stock& rbc = registry.single<stock>("tse:rbc");
    const etf& vab = registry.single<etf>("tse:vab");
    const bool& value = registry.single<bool>("tse:td");
    const std::tuple<stock, const bool>& many = registry.many<stock, bool>("tse:td");
    const std::vector<etf const*>& s = registry.all<etf>();
    const std::vector<stock const*>& s2 = registry.all<stock>();

    REQUIRE(s.size() == 1);
    REQUIRE(s2.size() == 2);
}

TEST_CASE("registry enroll mistakes", "[registry]")
{
    registry<stock, etf, bool> registry;

    registry.enroll<stock>({"tse:td", "tse:rbc"});
    registry.enroll<etf>({"tse:vab"});

    REQUIRE_THROWS_WITH(registry.enroll<stock>({"tse:td"}), "key is already enrolled");

    REQUIRE_THROWS_WITH(registry.single<stock>({"tse:not-found"}), "key is not found");
    REQUIRE_THROWS(registry.many<stock, bool>("tse:td"));
}
