set(HEADER_FILES
    include/lovely/controller/controller.h
    include/lovely/controller/executor/executor.h
    include/lovely/controller/exceptions.h
    include/lovely/controller/updater/updater.h
)

set(SOURCE_FILES
    src/controller.cpp
)

set(TARGET_CONTROLLER_NAME lovely_controller)

add_library(${TARGET_CONTROLLER_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${TARGET_CONTROLLER_NAME} PUBLIC include)
target_compile_features(${TARGET_CONTROLLER_NAME} PUBLIC cxx_std_17)
target_link_libraries(${TARGET_CONTROLLER_NAME} PUBLIC lovely_model)
install(TARGETS ${TARGET_CONTROLLER_NAME} DESTINATION lib)

set(TESTS_HEADER_FILES
    include/lovely/controller/tests/custom_controller.h
    include/lovely/controller/tests/executor/simple.h
    include/lovely/controller/tests/updater/custom_updater.h
)

set(TESTS_SOURCE_FILES
    src/tests_controller.cpp
)

set(TARGET_TESTS_CONTROLLER_NAME lovely_tests_controller)

add_library(${TARGET_TESTS_CONTROLLER_NAME} ${TESTS_SOURCE_FILES} ${TESTS_HEADER_FILES})
target_include_directories(${TARGET_TESTS_CONTROLLER_NAME} PUBLIC include)
target_compile_features(${TARGET_TESTS_CONTROLLER_NAME} PUBLIC cxx_std_17)
target_link_libraries(${TARGET_TESTS_CONTROLLER_NAME} PRIVATE lovely_tests_model)
target_link_libraries(${TARGET_TESTS_CONTROLLER_NAME} PUBLIC lovely_controller)
target_link_libraries(${TARGET_TESTS_CONTROLLER_NAME} PRIVATE ${TARGET_CONTROLLER_NAME})
install(TARGETS ${TARGET_TESTS_CONTROLLER_NAME} DESTINATION lib)

set(CONTROLLER_UNIT_TESTS controller-unit-tests)

set(SOURCES_CONTROLLER_UNIT_TESTS
    src/controller.main.tests.cpp
    src/controller/controller.tests.cpp
    src/controller/executor/executor.tests.cpp
    src/controller/tests/custom_controller.tests.cpp
    src/controller/tests/updater/custom_updater.tests.cpp
    src/controller/tests/executor/simple.tests.cpp
    src/controller/updater/updater.tests.cpp
)

add_executable(${CONTROLLER_UNIT_TESTS} ${SOURCES_CONTROLLER_UNIT_TESTS})
target_compile_features(${CONTROLLER_UNIT_TESTS} PRIVATE cxx_std_17)
target_link_libraries(${CONTROLLER_UNIT_TESTS} PRIVATE ${TARGET_CONTROLLER_NAME})
target_link_libraries(${CONTROLLER_UNIT_TESTS} PRIVATE ${TARGET_TESTS_CONTROLLER_NAME})
target_link_libraries(${CONTROLLER_UNIT_TESTS} PRIVATE Catch2::Catch2)

set(RUN_TEST_AFTER_BUILD true)

if (RUN_TEST_AFTER_BUILD)
    add_custom_command(
        TARGET ${CONTROLLER_UNIT_TESTS}
        COMMENT "run controller tests"
        POST_BUILD
        COMMAND ${CONTROLLER_UNIT_TESTS} ~long:*
    )
endif()
