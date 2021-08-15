#include <lovely/controller/controller.h>
#include <lovely/controller/tests/custom_controller.h>
#include <lovely/controller/tests/executor/simple.h>
#include <lovely/controller/tests/updater/custom_updater.h>
#include <lovely/controller/updater/updater.h>
#include <lovely/model/model.h>
#include <lovely/model/registry/registry.h>
#include <lovely/model/tests/model/custom_model.h>
#include <lovely/model/tests/symbol/etf.h>
#include <lovely/model/tests/symbol/stock.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("controller initialize", "[controller]")
{
    class simple_bis : public executor<custom_model> {
    public:
        simple_bis(custom_model& m) : executor<custom_model>(m) {}
        virtual ~simple_bis() = default;
    };

    const int int_ref = 42;

    custom_model model;
    model.initialize();

    controller<custom_model, custom_updater, simple<custom_model>, simple_bis> controller(model);

    int const* int_value_modified = nullptr;

    controller.update();
    model.cget("tse:td", int_value_modified);

    REQUIRE(*int_value_modified == int_ref + 10 + 1);

    controller.simple_math("tse:td", int_ref);
    model.cget("tse:td", int_value_modified);

    REQUIRE(*int_value_modified == int_ref + int_ref + 10 + 1);
}

TEST_CASE("controller throw when executors templates are not of executor base class", "[controller]")
{
    custom_model model;
    model.initialize();
    bool has_been_thrown = false;

    class fake_executor {
    public:
        fake_executor(custom_model& model) {}
    };

    try {
        controller<custom_model, custom_updater, fake_executor, simple<custom_model>> controller(model);
    }
    catch (...) {
        has_been_thrown = true;
    }

    REQUIRE(has_been_thrown == true);
}

TEST_CASE("controller throw when model not initialized", "[controller]")
{
    custom_model model_not_initialized;
    bool has_been_thrown = false;

    try {
        controller<custom_model, custom_updater, simple<custom_model>> controller(model_not_initialized);
    }
    catch (...) {
        has_been_thrown = true;
    }

    REQUIRE(has_been_thrown == true);
}
