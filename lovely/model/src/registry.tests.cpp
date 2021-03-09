#include <lovely/model/registry.h>
#include <lovely/model/symbol/etf.h>
#include <lovely/model/symbol/stock.h>

#include <array>
#include <catch2/catch.hpp>
#include <functional>
#include <limits>
#include <string>
#include <vector>

using namespace lovely;

TEST_CASE("listing enroll", "[listing]")
{
    listing<int> listing_1;
    listing<bool> listing_2;

    const int int_ref = 42;
    const bool bool_ref = true;

    listing_1.enroll("tse:rbc", int_ref);
    listing_2.enroll("tse:rbc", bool_ref);

    SECTION("enroll throw when required")
    {
        REQUIRE_THROWS(listing_1.enroll("tse:rbc", int_ref));
        REQUIRE_THROWS(listing_2.enroll("tse:rbc", bool_ref));
    }
}

TEST_CASE("listing get", "[listing]")
{
    listing<int> listing_1;
    listing<int> listing_2;

    const int int_ref = 42;

    listing_1.enroll("tse:rbc", int_ref);

    int int_value = 0;
    listing_1.get("tse:rbc", int_value);

    REQUIRE(int_value == int_ref);

    SECTION("set throw when required")
    {
        REQUIRE_THROWS(listing_1.get("tse:not-found", int_value));
        REQUIRE_THROWS(listing_2.get("tse:rbc", int_value));
    }
}

TEST_CASE("listing set", "[listing]")
{
    listing<int> listing_1;
    listing<int> listing_2;

    const int int_ref = 42;
    const int int_modified_ref = 41;

    listing_1.enroll("tse:rbc", int_ref);
    listing_1.set("tse:rbc", int_modified_ref);

    int int_value = 0;
    listing_1.get("tse:rbc", int_value);

    REQUIRE(int_value == int_modified_ref);

    SECTION("set throw when required")
    {
        REQUIRE_THROWS(listing_1.set("tse:not-found", int_modified_ref));
        REQUIRE_THROWS(listing_2.set("tse:rbc", int_modified_ref));
    }
}

TEST_CASE("listing all", "[listing]")
{
    listing<int> listing;

    const int int_ref = 42;
    const int int_ref_2 = 41;

    listing.enroll("tse:rbc", int_ref);
    listing.enroll("tse:td", int_ref_2);

    const auto& int_values = listing.all();

    REQUIRE(int_values[0] == int_ref);
    REQUIRE(int_values[1] == int_ref_2);
}

TEST_CASE("registry enroll", "[registry]")
{
    registry<stock, etf, bool, int> registry;

    const bool bool_ref = false;
    const int int_ref = 42;

    registry.enroll<stock>({{"tse:td", {}}, {"tse:rbc", {}}});
    registry.enroll<etf>({{"tse:vab", {}}});
    registry.enroll<bool>({{"tse:td", bool_ref}});
    registry.enroll<int>({{"tse:td", int_ref}});

    SECTION("enroll throw when enrolling already enrolled")
    {
        REQUIRE_THROWS(registry.enroll<stock>({{"tse:td", {}}}));
        REQUIRE_THROWS(registry.enroll<stock>({{"tse:rbc", {}}}));
    }
}

TEST_CASE("registry get", "[registry]")
{
    registry<stock, etf, bool, int> registry;

    const bool bool_ref = false;
    const int int_ref = 42;

    registry.enroll<stock>({{"tse:td", {}}, {"tse:rbc", {}}});
    registry.enroll<etf>({{"tse:vab", {}}});
    registry.enroll<bool>({{"tse:td", bool_ref}});
    registry.enroll<int>({{"tse:td", int_ref}});

    stock td;
    stock rbc;
    etf vab;
    bool bool_value = false;
    int int_value = 0;

    registry.get("tse:td", td);
    registry.get("tse:rbc", rbc);
    registry.get("tse:vab", vab);
    registry.get("tse:td", bool_value);
    registry.get("tse:td", int_value);

    REQUIRE(bool_value == bool_ref);
    REQUIRE(int_value == int_ref);

    REQUIRE_NOTHROW(registry.set("tse:td", !bool_ref));

    bool value_modified = bool_ref;
    registry.get("tse:td", value_modified);

    REQUIRE(value_modified == !bool_ref);

    SECTION("get throw when not found")
    {
        stock not_found;
        REQUIRE_THROWS(registry.get("tse:not-found", not_found));
        REQUIRE_THROWS(registry.set("tse:not-found", not_found));
    }
}

TEST_CASE("registry get_values", "[registry]")
{
    registry<stock, etf, bool, int> registry;

    const bool bool_ref = true;
    const int int_ref = 42;
    const int int_modified_ref = 41;

    registry.enroll<stock>({{"tse:td", {}}, {"tse:rbc", {}}});
    registry.enroll<etf>({{"tse:vab", {}}});
    registry.enroll<bool>({{"tse:td", bool_ref}});
    registry.enroll<int>({{"tse:td", int_ref}});

    bool td_bool_1 = false;
    bool td_bool_2 = false;
    bool td_bool_3 = false;

    stock td_stock_2;
    stock td_stock_3;

    int td_int_3 = 0;

    registry.get_values("tse:td", td_bool_1);
    registry.get_values("tse:td", td_bool_2, td_stock_2);
    registry.get_values("tse:td", td_bool_3, td_stock_3, td_int_3);

    REQUIRE(td_bool_1 == bool_ref);
    REQUIRE(td_bool_2 == bool_ref);
    REQUIRE(td_bool_3 == bool_ref);

    REQUIRE(td_int_3 == int_ref);

    REQUIRE_NOTHROW(registry.set_values("tse:td", bool_ref, int_modified_ref));

    bool td_bool_4 = false;
    int td_int_4 = 0;

    registry.get_values<bool, int>("tse:td", td_bool_4, td_int_4);
    REQUIRE(td_bool_4 == bool_ref);
    REQUIRE(td_int_4 == int_modified_ref);

    SECTION("many throw when not found")
    {
        stock not_found_stock;
        bool not_found_bool = false;
        REQUIRE_THROWS(registry.set_values("tse:not-found", not_found_stock, not_found_bool));
        REQUIRE_THROWS(registry.set_values("tse:vab", true));
    }
}

TEST_CASE("registry all", "[registry]")
{
    registry<stock, etf, bool, int> registry;

    const bool bool_ref = false;
    const int int_ref = 42;

    registry.enroll<etf>({{"tse:vab", {}}});
    registry.enroll<stock>({{"tse:td", {}}, {"tse:rbc", {}}});
    registry.enroll<bool>({{"tse:td", bool_ref}});

    const auto& s = registry.all<etf>();
    const auto& s_2 = registry.all<stock>();
    const auto& s_3 = registry.all<bool>();
    const auto& s_4 = registry.all<int>();

    REQUIRE(s.size() == 1);
    REQUIRE(s_2.size() == 2);
    REQUIRE(s_3.size() == 1);
    REQUIRE(s_3[0] == bool_ref);
    REQUIRE(s_4.size() == 0);
}
