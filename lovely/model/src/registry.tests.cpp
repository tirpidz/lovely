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
    registry<stock, etf, bool, int> registry;

    const bool bool_ref = false;
    const int int_ref = 42;

    registry.enroll<stock>({{"tse:td", {}}, {"tse:rbc", {}}});
    registry.enroll<etf>({{"tse:vab", {}}});
    registry.enroll<bool>({{"tse:td", bool_ref}});
    registry.enroll<int>({{"tse:td", int_ref}});

    const stock& td = registry.single<stock>("tse:td");
    const stock& rbc = registry.single<stock>("tse:rbc");
    const etf& vab = registry.single<etf>("tse:vab");
    const bool& value = registry.single<bool>("tse:td");

    REQUIRE(value == bool_ref);

    auto [td_stock, td_bool] = registry.many<stock, bool>("tse:td");
    const std::vector<etf const*>& s = registry.all<etf>();
    const std::vector<stock const*>& s2 = registry.all<stock>();

    REQUIRE(td_bool == bool_ref);
    REQUIRE(s.size() == 1);
    REQUIRE(s2.size() == 2);

    REQUIRE_NOTHROW(registry.set_single<bool>("tse:td", !bool_ref));

    const bool& value_modified = registry.single<bool>("tse:td");

    REQUIRE(value_modified == !bool_ref);

    REQUIRE_NOTHROW(registry.set_many("tse:td", bool_ref, int_ref - 1));
    auto [td_bool2, td_int] = registry.many<bool, int>("tse:td");
    REQUIRE(td_bool2 == bool_ref);
    REQUIRE(td_int == int_ref - 1);
}

TEST_CASE("registry enroll mistakes", "[registry]")
{
    registry<stock, etf, bool> registry;

    registry.enroll<stock>({{"tse:td", {}}, {"tse:rbc", {}}});
    registry.enroll<etf>({{"tse:vab", {}}});

    REQUIRE_THROWS(registry.enroll<stock>({{"tse:td", {}}}));
    REQUIRE_THROWS(registry.single<stock>({"tse:not-found"}));
    REQUIRE_THROWS(registry.many<stock, bool>("tse:td"));

    REQUIRE_THROWS(registry.set_single<stock>({"tse:not-found"}, {}));
    REQUIRE_THROWS(registry.set_many("tse:td", true));
}
