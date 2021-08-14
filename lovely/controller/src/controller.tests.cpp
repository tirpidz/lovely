#include <lovely/controller/controller.h>
#include <lovely/controller/executors/simple.h>
#include <lovely/controller/updater.h>
#include <lovely/model/model.h>
#include <lovely/model/registry.h>
#include <lovely/model/symbol/etf.h>
#include <lovely/model/symbol/stock.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("controller initialize", "[controller]")
{
    // const bool bool_ref = true;
    // const int int_ref = 42;

    // model<stock, etf, bool, int> model;
    // model.initialize();

    // auto update_external_callback = [&](lovely::model<stock, etf, bool, int>& model) { (void)model; };
    // auto update_derived_callback = [&](lovely::model<stock, etf, bool, int>& model) { (void)model; };

    // // updater<stock, etf, bool, int> updater(model, update_external_callback, update_derived_callback);

    // controller<typeof(model), typeof(updater), simple<typeof(model)>> controller(model, updater);

    // controller.simple_math("tse:td", int_ref);

    // int const* int_value_modified;
    // model.cget("tse:td", int_value_modified);

    // REQUIRE(*int_value_modified == 2 * int_ref);

    // SECTION("throw when callback is null")
    // {
    //     REQUIRE_THROWS(
    //         [&]() { lovely::updater<stock, etf, bool, int> updater(model, nullptr, update_derived_callback); }());
    //     REQUIRE_THROWS(
    //         [&]() { lovely::updater<stock, etf, bool, int> updater(model, update_external_callback, nullptr); }());
    //     REQUIRE_THROWS([&]() { lovely::updater<stock, etf, bool, int> updater(model, nullptr, nullptr); }());
    // }
}
