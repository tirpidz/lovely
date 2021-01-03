include_directories(${PROJECT_SOURCE_DIR})

set(HEADER_FILES
    fetch.h
)

set(SOURCE_FILES
    fetch.cpp
)

add_library(lovely_fetch ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(lovely_fetch PUBLIC .)
target_compile_features(lovely_fetch PUBLIC cxx_std_17)

include_directories(${PROJECT_SOURCE_DIR}/external/catch2/catch2/single_include/catch2)

set(FETCH_UNIT_TESTS fetch-unit-tests)

set(SOURCES_FETCH_UNIT_TESTS
    fetch.main.tests.cpp
    fetch.tests.cpp
)

add_executable(${FETCH_UNIT_TESTS} ${SOURCES_FETCH_UNIT_TESTS})
target_compile_features(${FETCH_UNIT_TESTS} PRIVATE cxx_std_17)
target_link_libraries(${FETCH_UNIT_TESTS} PRIVATE lovely_fetch)

set(RUN_TEST_AFTER_BUILD true)

if (RUN_TEST_AFTER_BUILD)
    add_custom_command(
        TARGET ${FETCH_UNIT_TESTS}
        COMMENT "Run Fetch tests"
        POST_BUILD
        COMMAND ${FETCH_UNIT_TESTS} ~long:*
    )
endif()
