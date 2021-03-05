#include <lovely/controller/controller.h>
#include <lovely/model/model.h>
#include <lovely/model/registry.h>
#include <lovely/model/symbol/etf.h>
#include <lovely/model/symbol/stock.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("controller initialize", "[controller]")
{
    const bool bool_ref = true;
    const int int_ref = 42;

    auto initialization_callback = [&](registry<stock, etf, bool, int>& data) {
        data.enroll<stock>({{"tse:td", {}}, {"tse:rbc", {}}});
        data.enroll<etf>({{"tse:vab", {}}});
        data.enroll<bool>({{"tse:td", bool_ref}});
        data.enroll<int>({{"tse:td", int_ref}});
    };

    model<stock, etf, bool, int> model(initialization_callback);
    model.initialize();

    auto update_external_callback = [&](lovely::model<stock, etf, bool, int>& model) { (void)model; };
    auto update_derived_callback = [&](lovely::model<stock, etf, bool, int>& model) { (void)model; };

    controller<stock, etf, bool, int> controller(model, update_external_callback, update_derived_callback);

    SECTION("throw when callback is null")
    {
        REQUIRE_THROWS(
            [&]() { lovely::controller<stock, etf, bool, int> controller(model, nullptr, update_derived_callback); }());
        REQUIRE_THROWS([&]() {
            lovely::controller<stock, etf, bool, int> controller(model, update_external_callback, nullptr);
        }());
        REQUIRE_THROWS([&]() { lovely::controller<stock, etf, bool, int> controller(model, nullptr, nullptr); }());
    }

    SECTION("throw when model is not initialized")
    {
        lovely::model<stock, etf, bool, int> uninitialized_model(initialization_callback);

        REQUIRE_THROWS([&]() {
            lovely::controller<stock, etf, bool, int> controller(uninitialized_model, update_external_callback,
                                                                 update_derived_callback);
        }());
    }
}
