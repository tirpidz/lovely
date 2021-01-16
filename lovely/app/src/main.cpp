#include <lovely/version.h>

#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "name: " << lovely::LovelyName << std::endl;
    std::cout << "version: " << lovely::LovelyVersion << std::endl;
    std::cout << "major: " << lovely::LovelyMajorVersion << std::endl;
    std::cout << "minor: " << lovely::LovelyMinorVersion << std::endl;
    std::cout << "patch: " << lovely::LovelyPatchVersion << std::endl;
    std::cout << "build timestamp: " << lovely::LovelyBuildTimestamp << std::endl;
    std::cout << "commit: " << lovely::LovelyCommit << std::endl;
    return 0;
}