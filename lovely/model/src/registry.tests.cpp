#include <lovely/model/registry.h>
#include <lovely/model/symbol/etf.h>
#include <lovely/model/symbol/stock.h>

#include <catch2/catch.hpp>
#include <functional>
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

    SECTION("enroll throw when required")
    {
        REQUIRE_THROWS(registry.enroll<stock>({{"tse:td", {}}}));
        REQUIRE_THROWS(registry.enroll<stock>({{"tse:rbc", {}}}));
    }
}

TEST_CASE("registry single", "[registry]")
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
    const bool& bool_value = registry.single<bool>("tse:td");
    const int& int_value = registry.single<int>("tse:td");

    REQUIRE(bool_value == bool_ref);
    REQUIRE(int_value == int_ref);

    REQUIRE_NOTHROW(registry.set_single<bool>("tse:td", !bool_ref));

    const bool& value_modified = registry.single<bool>("tse:td");

    REQUIRE(value_modified == !bool_ref);

    SECTION("single throw when required")
    {
        REQUIRE_THROWS(registry.single<stock>({"tse:not-found"}));
        REQUIRE_THROWS(registry.set_single<stock>({"tse:not-found"}, {}));
    }
}

TEST_CASE("registry many", "[registry]")
{
    registry<stock, etf, bool, int> registry;

    const bool bool_ref = false;
    const int int_ref = 42;
    const int int_modified_ref = 41;

    registry.enroll<stock>({{"tse:td", {}}, {"tse:rbc", {}}});
    registry.enroll<etf>({{"tse:vab", {}}});
    registry.enroll<bool>({{"tse:td", bool_ref}});
    registry.enroll<int>({{"tse:td", int_ref}});

    auto [td_bool_1] = registry.many<bool>("tse:td");
    auto [td_stock_2, td_bool_2] = registry.many<stock, bool>("tse:td");
    auto [td_stock_3, td_bool_3, td_int_3] = registry.many<stock, bool, int>("tse:td");

    REQUIRE(td_bool_1 == bool_ref);
    REQUIRE(td_bool_2 == bool_ref);
    REQUIRE(td_bool_3 == bool_ref);

    REQUIRE(td_int_3 == int_ref);

    REQUIRE_NOTHROW(registry.set_many("tse:td", bool_ref, int_modified_ref));
    auto [td_bool_4, td_int_4] = registry.many<bool, int>("tse:td");
    REQUIRE(td_bool_4 == bool_ref);
    REQUIRE(td_int_4 == int_modified_ref);

    SECTION("many throw when required")
    {
        REQUIRE_THROWS(registry.many<stock, bool>("tse:not-found"));
        REQUIRE_THROWS(registry.set_many<bool>("tse:vab", true));
    }
}

TEST_CASE("registry all", "[registry]")
{
    registry<stock, etf, bool, int> registry;

    const bool bool_ref = false;
    const int int_ref = 42;

    registry.enroll<stock>({{"tse:td", {}}, {"tse:rbc", {}}});
    registry.enroll<etf>({{"tse:vab", {}}});
    registry.enroll<bool>({{"tse:td", bool_ref}});

    const std::vector<std::reference_wrapper<etf>>& s = registry.all<etf>();
    const std::vector<std::reference_wrapper<stock>>& s_2 = registry.all<stock>();
    const std::vector<std::reference_wrapper<bool>>& s_3 = registry.all<bool>();
    const std::vector<std::reference_wrapper<int>>& s_4 = registry.all<int>();

    REQUIRE(s.size() == 1);
    REQUIRE(s_2.size() == 2);
    REQUIRE(s_3.size() == 1);
    REQUIRE(s_3[0] == bool_ref);
    REQUIRE(s_4.size() == 0);
}
