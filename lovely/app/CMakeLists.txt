find_package(Git QUIET REQUIRED)

set(MAIN main)

set(HEADER_FILES
    include/lovely/version.h
)

set(TARGET_VERSION_NAME lovely_version)

add_library(${TARGET_VERSION_NAME} ${HEADER_FILES})
set_target_properties(${TARGET_VERSION_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${TARGET_VERSION_NAME} PUBLIC include)
target_compile_features(${TARGET_VERSION_NAME} PUBLIC cxx_std_17)

set(SOURCES_MAIN
    src/main.cpp
)

add_executable(${MAIN} ${SOURCES_MAIN})
target_compile_features(${MAIN} PRIVATE cxx_std_17)
target_link_libraries(${MAIN} PRIVATE lovely_controller)
target_link_libraries(${MAIN} PRIVATE lovely_model)
target_link_libraries(${MAIN} PRIVATE lovely_view)
target_link_libraries(${MAIN} PRIVATE lovely_version)

execute_process(
    COMMAND "${GIT_EXECUTABLE}" describe --always --tags --abbrev=0
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    OUTPUT_VARIABLE LOVELY_TAG_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)

execute_process(
    COMMAND "${GIT_EXECUTABLE}" rev-parse --short HEAD
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    OUTPUT_VARIABLE LOVELY_COMMIT_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)

string(TIMESTAMP LOVELY_BUILD_TIMESTAMP)

configure_file(
  "${PROJECT_SOURCE_DIR}/lovely/app/version.h.in"
  "${PROJECT_SOURCE_DIR}/lovely/app/include/lovely/version.h"
)
