#include <lovely/api/api.h>
#include <lovely/fetch/fetch.h>
#include <lovely/window/window.h>

#include <iostream>

int main(int argc, char* argv[]) {
    lovely::api api;
    lovely::fetch fetch;
    lovely::window window;

    std::cout << "api: " << api.number() << std::endl;
    std::cout << "fetch: " << fetch.number() << std::endl;
    std::cout << "window: " << window.number() << std::endl;

    return 0;
}