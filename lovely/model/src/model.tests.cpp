#include <lovely/model/model.h>
#include <lovely/model/symbol/etf.h>
#include <lovely/model/symbol/stock.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("model enroll", "[model]")
{
    model<stock, etf, bool, int> model;

    const bool bool_ref = true;
    const int int_ref = 42;

    model.initialize([&](registry<stock, etf, bool, int>& data) {
        data.enroll<stock>({{"tse:td", {}}, {"tse:rbc", {}}});
        data.enroll<etf>({{"tse:vab", {}}});
        data.enroll<bool>({{"tse:td", bool_ref}});
        data.enroll<int>({{"tse:td", int_ref}});
    });

    const auto& data = model.data();

    const bool& bool_value = data.single<bool>("tse:td");
    const int& int_value = data.single<int>("tse:td");

    REQUIRE(bool_value == bool_ref);
    REQUIRE(int_value == int_ref);

    SECTION("enroll throw when trying to enroll a second time")
    {
        REQUIRE_THROWS(model.initialize([&](registry<stock, etf, bool, int>& data) {
            data.enroll<stock>({{"tse:td", {}}, {"tse:rbc", {}}});
            data.enroll<etf>({{"tse:vab", {}}});
            data.enroll<bool>({{"tse:td", bool_ref}});
            data.enroll<int>({{"tse:td", int_ref}});
        }));
    }
}
