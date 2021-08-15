#include <lovely/model/tests/model/custom_model.h>
#include <lovely/view/view.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("view initialize", "[view]")
{
    custom_model model;
    model.initialize();

    view<custom_model> view(model);
}

TEST_CASE("view throw when model not initialized", "[controller]")
{
    custom_model model_not_initialized;
    bool has_been_thrown = false;

    try {
        view<custom_model> view(model_not_initialized);
    }
    catch (...) {
        has_been_thrown = true;
    }

    REQUIRE(has_been_thrown == true);
}
