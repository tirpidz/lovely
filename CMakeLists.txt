cmake_minimum_required(VERSION 3.10.2...3.17.2)

project(Lovely
  VERSION 
  0.0.0 
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS -pthread)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

add_subdirectory(lovely/external/catch2)
add_subdirectory(lovely/app)
add_subdirectory(lovely/controller)
add_subdirectory(lovely/model)
add_subdirectory(lovely/view)
