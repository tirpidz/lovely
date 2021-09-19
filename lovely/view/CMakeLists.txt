file(GLOB_RECURSE HEADER_FILES LIST_DIRECTORIES false "*.h")
list(FILTER HEADER_FILES EXCLUDE REGEX "tests")

file(GLOB_RECURSE SOURCE_FILES LIST_DIRECTORIES false "*.cpp")
list(FILTER SOURCE_FILES EXCLUDE REGEX "tests")

set(TARGET_VIEW_NAME lovely_view)

add_library(${TARGET_VIEW_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${TARGET_VIEW_NAME} PUBLIC include)
target_compile_features(${TARGET_VIEW_NAME} PUBLIC cxx_std_17)
target_link_libraries(${TARGET_VIEW_NAME} PUBLIC lovely_model)
install(TARGETS ${TARGET_VIEW_NAME} DESTINATION lib)

file(GLOB_RECURSE TESTS_HEADER_FILES LIST_DIRECTORIES false "*.h")
list(FILTER TESTS_HEADER_FILES INCLUDE REGEX "tests")

file(GLOB_RECURSE TESTS_SOURCE_FILES LIST_DIRECTORIES false "tests_*.cpp")

set(TARGET_TESTS_VIEW_NAME lovely_tests_view)

add_library(${TARGET_TESTS_VIEW_NAME} ${TESTS_SOURCE_FILES} ${TESTS_HEADER_FILES})
target_include_directories(${TARGET_TESTS_VIEW_NAME} PUBLIC include)
target_compile_features(${TARGET_TESTS_VIEW_NAME} PUBLIC cxx_std_17)
target_link_libraries(${TARGET_TESTS_VIEW_NAME} PUBLIC lovely_tests_model)
target_link_libraries(${TARGET_TESTS_VIEW_NAME} PUBLIC lovely_tests_controller)
target_link_libraries(${TARGET_TESTS_VIEW_NAME} PRIVATE ${TARGET_VIEW_NAME})
install(TARGETS ${TARGET_TESTS_VIEW_NAME} DESTINATION lib)

set(VIEW_UNIT_TESTS view-unit-tests)

file(GLOB_RECURSE SOURCES_VIEW_UNIT_TESTS LIST_DIRECTORIES false "*tests.cpp")

add_executable(${VIEW_UNIT_TESTS} ${SOURCES_VIEW_UNIT_TESTS})
target_compile_features(${VIEW_UNIT_TESTS} PRIVATE cxx_std_17)
target_link_libraries(${VIEW_UNIT_TESTS} PRIVATE ${TARGET_VIEW_NAME})
target_link_libraries(${VIEW_UNIT_TESTS} PRIVATE ${TARGET_TESTS_VIEW_NAME})
target_link_libraries(${VIEW_UNIT_TESTS} PRIVATE Catch2::Catch2)

set(RUN_TEST_AFTER_BUILD true)

if (RUN_TEST_AFTER_BUILD)
    add_custom_command(
        TARGET ${VIEW_UNIT_TESTS}
        COMMENT "run view tests"
        POST_BUILD
        COMMAND ${VIEW_UNIT_TESTS} ~long:*
    )
endif()
