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

    int const* int_value = nullptr;
    int* int_value_2 = nullptr;
    listing_1.cget("tse:rbc", int_value);
    listing_1.get("tse:rbc", int_value_2);

    REQUIRE(*int_value == int_ref);
    REQUIRE(*int_value_2 == int_ref);

    SECTION("set throw when required")
    {
        REQUIRE_THROWS(listing_1.cget("tse:not-found", int_value));
        REQUIRE_THROWS(listing_2.cget("tse:rbc", int_value));
        REQUIRE_THROWS(listing_1.get("tse:not-found", int_value_2));
        REQUIRE_THROWS(listing_2.get("tse:rbc", int_value_2));
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

    int const* int_value = nullptr;
    int* int_value_2 = nullptr;
    listing_1.cget("tse:rbc", int_value);
    listing_1.get("tse:rbc", int_value_2);

    REQUIRE(*int_value == int_modified_ref);
    REQUIRE(*int_value_2 == int_modified_ref);

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

    std::vector<int const*> all;
    std::vector<int*> all_2;

    listing.call(all);
    listing.all(all_2);

    REQUIRE(*(all[0]) == int_ref);
    REQUIRE(*(all[1]) == int_ref_2);
    REQUIRE(*(all_2[0]) == int_ref);
    REQUIRE(*(all_2[1]) == int_ref_2);
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

TEST_CASE("registry geT and set", "[registry]")
{
    registry<stock, etf, bool, int> registry;

    const bool bool_ref = false;
    const int int_ref = 42;

    registry.enroll<stock>({{"tse:td", {}}, {"tse:rbc", {}}});
    registry.enroll<etf>({{"tse:vab", {}}});
    registry.enroll<bool>({{"tse:td", bool_ref}});
    registry.enroll<int>({{"tse:td", int_ref}});

    stock const* td = nullptr;
    stock const* rbc = nullptr;
    etf const* vab = nullptr;
    bool const* bool_value = nullptr;
    int const* int_value = nullptr;

    stock* td_2 = nullptr;
    stock* rbc_2 = nullptr;
    etf* vab_2 = nullptr;
    bool* bool_value_2 = nullptr;
    int* int_value_2 = nullptr;

    registry.cget("tse:td", td);
    registry.cget("tse:rbc", rbc);
    registry.cget("tse:vab", vab);
    registry.cget("tse:td", bool_value);
    registry.cget("tse:td", int_value);

    registry.get("tse:td", td_2);
    registry.get("tse:rbc", rbc_2);
    registry.get("tse:vab", vab_2);
    registry.get("tse:td", bool_value_2);
    registry.get("tse:td", int_value_2);

    REQUIRE(*bool_value == bool_ref);
    REQUIRE(*int_value == int_ref);

    REQUIRE(*bool_value_2 == bool_ref);
    REQUIRE(*int_value_2 == int_ref);

    REQUIRE_NOTHROW(registry.set("tse:td", !bool_ref));

    bool const* value_modified = nullptr;
    bool* value_modified_2 = nullptr;

    registry.cget("tse:td", value_modified);
    registry.get("tse:td", value_modified_2);

    REQUIRE(*value_modified == !bool_ref);
    REQUIRE(*value_modified_2 == !bool_ref);

    SECTION("get throw when not found")
    {
        stock const* not_found = nullptr;
        stock* not_found_2 = nullptr;
        REQUIRE_THROWS(registry.cget("tse:not-found", not_found));
        REQUIRE_THROWS(registry.get("tse:not-found", not_found_2));
        REQUIRE_THROWS(registry.set("tse:not-found", true));
    }
}

TEST_CASE("registry get and set multiple arguments", "[registry]")
{
    registry<stock, etf, bool, int> registry;

    const bool bool_ref = true;
    const int int_ref = 42;
    const int int_modified_ref = 41;

    registry.enroll<stock>({{"tse:td", {}}, {"tse:rbc", {}}});
    registry.enroll<etf>({{"tse:vab", {}}});
    registry.enroll<bool>({{"tse:td", bool_ref}});
    registry.enroll<int>({{"tse:td", int_ref}});

    bool const* td_bool_1 = nullptr;
    bool const* td_bool_2 = nullptr;
    bool const* td_bool_3 = nullptr;

    stock const* td_stock_2 = nullptr;
    stock const* td_stock_3 = nullptr;

    int const* td_int_3 = nullptr;

    bool* td_bool_1_2 = nullptr;
    bool* td_bool_2_2 = nullptr;
    bool* td_bool_3_2 = nullptr;

    stock* td_stock_2_2 = nullptr;
    stock* td_stock_3_2 = nullptr;

    int* td_int_3_2 = nullptr;

    registry.cget("tse:td", td_bool_1);
    registry.cget("tse:td", td_bool_2, td_stock_2);
    registry.cget("tse:td", td_bool_3, td_stock_3, td_int_3);

    registry.get("tse:td", td_bool_1_2);
    registry.get("tse:td", td_bool_2_2, td_stock_2_2);
    registry.get("tse:td", td_bool_3_2, td_stock_3_2, td_int_3_2);

    REQUIRE(*td_bool_1 == bool_ref);
    REQUIRE(*td_bool_2 == bool_ref);
    REQUIRE(*td_bool_3 == bool_ref);

    REQUIRE(*td_int_3 == int_ref);

    REQUIRE(*td_bool_1_2 == bool_ref);
    REQUIRE(*td_bool_2_2 == bool_ref);
    REQUIRE(*td_bool_3_2 == bool_ref);

    REQUIRE(*td_int_3_2 == int_ref);

    REQUIRE_NOTHROW(registry.set("tse:td", int_modified_ref));
    REQUIRE_NOTHROW(registry.set("tse:td", bool_ref, int_modified_ref));

    bool const* td_bool_4 = nullptr;
    int const* td_int_4 = nullptr;

    bool* td_bool_4_2 = nullptr;
    int* td_int_4_2 = nullptr;

    registry.cget("tse:td", td_bool_4, td_int_4);

    registry.get("tse:td", td_bool_4_2, td_int_4_2);

    REQUIRE(*td_bool_4 == bool_ref);
    REQUIRE(*td_int_4 == int_modified_ref);

    REQUIRE(*td_bool_4_2 == bool_ref);
    REQUIRE(*td_int_4_2 == int_modified_ref);

    SECTION("many throw when not found")
    {
        stock not_found_stock;
        bool not_found_bool = false;
        REQUIRE_THROWS(registry.set("tse:vab", not_found_bool));
        REQUIRE_THROWS(registry.set("tse:not-found", not_found_stock, not_found_bool));
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

    std::vector<etf const*> s_1;
    std::vector<stock const*> s_2;
    std::vector<bool const*> s_3;
    std::vector<int const*> s_4;

    std::vector<etf*> s_1_2;
    std::vector<stock*> s_2_2;
    std::vector<bool*> s_3_2;
    std::vector<int*> s_4_2;

    registry.call(s_1);
    registry.call(s_2);
    registry.call(s_3);
    registry.call(s_4);

    registry.all(s_1_2);
    registry.all(s_2_2);
    registry.all(s_3_2);
    registry.all(s_4_2);

    REQUIRE(s_1.size() == 1);
    REQUIRE(s_2.size() == 2);
    REQUIRE(s_3.size() == 1);
    REQUIRE(*(s_3[0]) == bool_ref);
    REQUIRE(s_4.size() == 0);

    REQUIRE(s_1_2.size() == 1);
    REQUIRE(s_2_2.size() == 2);
    REQUIRE(s_3_2.size() == 1);
    REQUIRE(*(s_3_2[0]) == bool_ref);
    REQUIRE(s_4_2.size() == 0);
}
