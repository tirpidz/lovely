#include <lovely/controller/updater.h>
#include <lovely/model/model.h>
#include <lovely/model/registry.h>
#include <lovely/model/symbol/etf.h>
#include <lovely/model/symbol/stock.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("updater initialize", "[controller]")
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

    class custom_updater : public updater<custom_model> {
    public:
        custom_updater(custom_model& model) : updater<custom_model>(model) {}

    protected:
        virtual void update_external_internal() override
        {
            int* int_value = nullptr;
            _model.get("tse:td", int_value);
            *int_value += 1;
        }

        virtual void update_derived_internal() override
        {
            int* int_value = nullptr;
            _model.get("tse:td", int_value);
            *int_value += 10;
        }
    };

    const int int_ref = 42;

    custom_model model;
    model.initialize();

    custom_updater updater(model);

    int const* int_value_modified = nullptr;

    updater.update();
    model.cget("tse:td", int_value_modified);

    REQUIRE(*int_value_modified == int_ref + 10 + 1);
}
