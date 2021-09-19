file(GLOB_RECURSE HEADER_FILES LIST_DIRECTORIES false "*.h")
list(FILTER HEADER_FILES EXCLUDE REGEX "tests")

file(GLOB_RECURSE SOURCE_FILES LIST_DIRECTORIES false "*.cpp")
list(FILTER SOURCE_FILES EXCLUDE REGEX "tests")

set(TARGET_MODEL_NAME lovely_model)

add_library(${TARGET_MODEL_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${TARGET_MODEL_NAME} PUBLIC include)
target_compile_features(${TARGET_MODEL_NAME} PUBLIC cxx_std_17)
install(TARGETS ${TARGET_MODEL_NAME} DESTINATION lib)

set(MODEL_UNIT_TESTS model-unit-tests)

file(GLOB_RECURSE TESTS_HEADER_FILES LIST_DIRECTORIES false "*.h")
list(FILTER TESTS_HEADER_FILES INCLUDE REGEX "tests")

file(GLOB_RECURSE TESTS_SOURCE_FILES LIST_DIRECTORIES false "tests_*.cpp")

set(TARGET_TESTS_MODEL_NAME lovely_tests_model)

add_library(${TARGET_TESTS_MODEL_NAME} ${TESTS_SOURCE_FILES} ${TESTS_HEADER_FILES})
target_include_directories(${TARGET_TESTS_MODEL_NAME} PUBLIC include)
target_compile_features(${TARGET_TESTS_MODEL_NAME} PUBLIC cxx_std_17)
target_link_libraries(${TARGET_TESTS_MODEL_NAME} PRIVATE ${TARGET_MODEL_NAME})
install(TARGETS ${TARGET_TESTS_MODEL_NAME} DESTINATION lib)

file(GLOB_RECURSE SOURCES_MODEL_UNIT_TESTS LIST_DIRECTORIES false "*tests.cpp")

add_executable(${MODEL_UNIT_TESTS} ${SOURCES_MODEL_UNIT_TESTS})
target_compile_features(${MODEL_UNIT_TESTS} PRIVATE cxx_std_17)
target_link_libraries(${MODEL_UNIT_TESTS} PRIVATE ${TARGET_MODEL_NAME})
target_link_libraries(${MODEL_UNIT_TESTS} PRIVATE ${TARGET_TESTS_MODEL_NAME})
target_link_libraries(${MODEL_UNIT_TESTS} PRIVATE Catch2::Catch2)

set(RUN_TEST_AFTER_BUILD true)

if (RUN_TEST_AFTER_BUILD)
    add_custom_command(
        TARGET ${MODEL_UNIT_TESTS}
        COMMENT "run model tests"
        POST_BUILD
        COMMAND ${MODEL_UNIT_TESTS} ~long:*
    )
endif()
