#include <lovely/model/model.h>
#include <lovely/model/tests/symbol/etf.h>
#include <lovely/model/tests/symbol/stock.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("model initialize", "[model]")
{
    const bool bool_ref = true;
    const int int_ref = 42;

    model<stock, etf, bool, int> model;
    REQUIRE(!model.is_initialized());
    model.initialize();
    REQUIRE(model.is_initialized());

    SECTION("throw when trying to initialize a second time") { REQUIRE_THROWS(model.initialize()); }
}

TEST_CASE("custom model initialize", "[model]")
{
    class custom_model : public model<stock, etf, bool, int> {
    protected:
        virtual void initialize_internal() override
        {
            enroll<stock>({{"tse:td", {}}, {"tse:rbc", {}}});
            enroll<etf>({{"tse:vab", {}}});
            enroll<bool>({{"tse:td", true}});
            enroll<int>({{"tse:td", 42}});
        }
    };

    const bool bool_ref = true;
    const int int_ref = 42;

    custom_model model;
    model.initialize();

    bool const* bool_value = nullptr;
    int* int_value = nullptr;

    model.cget("tse:td", bool_value);
    model.get("tse:td", int_value);

    REQUIRE(*bool_value == bool_ref);
    REQUIRE(*int_value == int_ref);
}
