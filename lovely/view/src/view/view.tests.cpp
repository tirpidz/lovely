#include <lovely/controller/controller.h>
#include <lovely/controller/tests/custom_controller.h>
#include <lovely/model/model.h>
#include <lovely/model/tests/model/custom_model.h>
#include <lovely/view/view.h>

#include <catch2/catch.hpp>

using namespace lovely;

TEST_CASE("view initialize", "[view]")
{
    custom_model model;
    custom_controller controller(model);
    
}
