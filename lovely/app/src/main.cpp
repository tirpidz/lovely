#include <lovely/controller/controller.h>
#include <lovely/model/model.h>
#include <lovely/version.h>
#include <lovely/view/view.h>

#include <iostream>

using namespace lovely;

int main(int argc, char* argv[]) {
    controller::controller controller;
    model::model model;
    view::view view;

    std::cout << "controller: " << controller.number() << std::endl;
    std::cout << "model: " << model.number() << std::endl;
    std::cout << "view: " << view.number() << std::endl;

    return 0;
}