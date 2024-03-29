#include <lovely/controller/updater/updater.h>
#include <lovely/model/model.h>
#include <lovely/model/tests/model/custom_model.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("updater initialize", "[controller]")
{
    const int int_ref = 42;

    custom_model model;
    model.initialize();

    updater<custom_model> updater(model);

    int const* int_value_modified = nullptr;

    updater.update();
    model.cget("tse:td", int_value_modified);

    REQUIRE(*int_value_modified == int_ref);
}

TEST_CASE("updater throw when model not initialized", "[controller]")
{
    custom_model model_not_initialized;
    bool has_been_thrown = false;

    try {
        updater<custom_model> updater(model_not_initialized);
    }
    catch (...) {
        has_been_thrown = true;
    }

    REQUIRE(has_been_thrown == true);
}
