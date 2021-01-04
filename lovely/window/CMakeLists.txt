include_directories(${PROJECT_SOURCE_DIR})

set(HEADER_FILES
    window.h
)

set(SOURCE_FILES
    window.cpp
)

add_library(lovely_window ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(lovely_window PUBLIC .)
target_compile_features(lovely_window PUBLIC cxx_std_17)
target_link_libraries(lovely_window PRIVATE lovely_api)
target_link_libraries(lovely_window PRIVATE lovely_fetch)

include_directories(${PROJECT_SOURCE_DIR}/external/catch2/catch2/single_include/catch2)

set(WINDOW_UNIT_TESTS window-unit-tests)

set(SOURCES_WINDOW_UNIT_TESTS
    window.main.tests.cpp
    window.tests.cpp
)

add_executable(${WINDOW_UNIT_TESTS} ${SOURCES_WINDOW_UNIT_TESTS})
target_compile_features(${WINDOW_UNIT_TESTS} PRIVATE cxx_std_17)
target_link_libraries(${WINDOW_UNIT_TESTS} PRIVATE lovely_window)

set(RUN_TEST_AFTER_BUILD true)

if (RUN_TEST_AFTER_BUILD)
    add_custom_command(
        TARGET ${WINDOW_UNIT_TESTS}
        COMMENT "Run Window tests"
        POST_BUILD
        COMMAND ${WINDOW_UNIT_TESTS} ~long:*
    )
endif()
