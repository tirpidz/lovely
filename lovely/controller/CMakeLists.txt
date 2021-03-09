set(HEADER_FILES
    include/lovely/controller/controller.h
    include/lovely/controller/exceptions.h
    include/lovely/controller/executors/simple.h
    include/lovely/controller/updater.h
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

set(CONTROLLER_UNIT_TESTS controller-unit-tests)

set(SOURCES_CONTROLLER_UNIT_TESTS
    src/controller.main.tests.cpp
    src/controller.tests.cpp
)

add_executable(${CONTROLLER_UNIT_TESTS} ${SOURCES_CONTROLLER_UNIT_TESTS})
target_compile_features(${CONTROLLER_UNIT_TESTS} PRIVATE cxx_std_17)
target_link_libraries(${CONTROLLER_UNIT_TESTS} PRIVATE ${TARGET_CONTROLLER_NAME})
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
