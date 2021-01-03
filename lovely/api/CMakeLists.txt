include_directories(${PROJECT_SOURCE_DIR})

set(HEADER_FILES
    api.h
)

set(SOURCE_FILES
    api.cpp
)

add_library(lovely_api ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(lovely_api PUBLIC .)
target_compile_features(lovely_api PUBLIC cxx_std_17)

include_directories(${PROJECT_SOURCE_DIR}/external/catch2/catch2/single_include/catch2)

set(API_UNIT_TESTS api-unit-tests)

set(SOURCES_API_UNIT_TESTS
    api.main.tests.cpp
    api.tests.cpp
)

add_executable(${API_UNIT_TESTS} ${SOURCES_API_UNIT_TESTS})
target_compile_features(${API_UNIT_TESTS} PRIVATE cxx_std_17)
target_link_libraries(${API_UNIT_TESTS} PRIVATE lovely_api)

set(RUN_TEST_AFTER_BUILD true)

if (RUN_TEST_AFTER_BUILD)
    add_custom_command(
        TARGET ${API_UNIT_TESTS}
        COMMENT "Run Api tests"
        POST_BUILD
        COMMAND ${API_UNIT_TESTS} ~long:*
    )
endif()
