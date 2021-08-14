#include <lovely/model/registry/listing.h>
#include <lovely/model/tests/symbol/etf.h>
#include <lovely/model/tests/symbol/stock.h>

#include <array>
#include <catch2/catch.hpp>
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