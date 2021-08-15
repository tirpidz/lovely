#include <lovely/controller/executor/executor.h>
#include <lovely/controller/updater/updater.h>
#include <lovely/model/model.h>
#include <lovely/model/tests/model/custom_model.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("executor initialize", "[controller]")
{
    const int int_ref = 42;

    custom_model model;
    model.initialize();

    executor<custom_model> exectuor(model);
}

TEST_CASE("executor throw when model not initialized", "[controller]")
{
    custom_model model_not_initialized;
    bool has_been_thrown = false;

    try {
        executor<custom_model> executor(model_not_initialized);
    }
    catch (...) {
        has_been_thrown = true;
    }

    REQUIRE(has_been_thrown == true);
}
