include_directories(${PROJECT_SOURCE_DIR})
include_directories(${CATCH2_INCLUDE_DIRECTORY})

set(HEADER_FILES
    controller.h
)

set(SOURCE_FILES
    controller.cpp
)

set(TARGET_CONTROLLER_NAME lovely_controller)
set(LIBRARY_CONTROLLER_NAME ${TARGET_CONTROLLER_NAME} PARENT_SCOPE)

add_library(${TARGET_CONTROLLER_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${TARGET_CONTROLLER_NAME} PUBLIC .)
target_compile_features(${TARGET_CONTROLLER_NAME} PUBLIC cxx_std_17)
target_link_libraries(${TARGET_CONTROLLER_NAME} PRIVATE ${LIBRARY_MODEL_NAME})

set(CONTROLLER_UNIT_TESTS controller-unit-tests)

set(SOURCES_CONTROLLER_UNIT_TESTS
    controller.main.tests.cpp
    controller.tests.cpp
)

add_executable(${CONTROLLER_UNIT_TESTS} ${SOURCES_CONTROLLER_UNIT_TESTS})
target_compile_features(${CONTROLLER_UNIT_TESTS} PRIVATE cxx_std_17)
target_link_libraries(${CONTROLLER_UNIT_TESTS} PRIVATE ${TARGET_CONTROLLER_NAME})

set(RUN_TEST_AFTER_BUILD true)

if (RUN_TEST_AFTER_BUILD)
    add_custom_command(
        TARGET ${CONTROLLER_UNIT_TESTS}
        COMMENT "run controller tests"
        POST_BUILD
        COMMAND ${CONTROLLER_UNIT_TESTS} ~long:*
    )
endif()
