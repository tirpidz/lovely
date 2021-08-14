set(HEADER_FILES
    include/lovely/view/view.h
)

set(SOURCE_FILES
    src/view.cpp
)

set(TARGET_VIEW_NAME lovely_view)

add_library(${TARGET_VIEW_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${TARGET_VIEW_NAME} PUBLIC include)
target_compile_features(${TARGET_VIEW_NAME} PUBLIC cxx_std_17)
target_link_libraries(${TARGET_VIEW_NAME} PUBLIC lovely_controller)
target_link_libraries(${TARGET_VIEW_NAME} PUBLIC lovely_model)
install(TARGETS ${TARGET_VIEW_NAME} DESTINATION lib)

set(TESTS_HEADER_FILES
    include/lovely/view/tests/view/stock_view.h
)

set(TESTS_SOURCE_FILES
    src/tests_view.cpp
)

set(TARGET_TESTS_VIEW_NAME lovely_tests_view)

add_library(${TARGET_TESTS_VIEW_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${TARGET_TESTS_VIEW_NAME} PUBLIC include)
target_compile_features(${TARGET_TESTS_VIEW_NAME} PUBLIC cxx_std_17)
install(TARGETS ${TARGET_TESTS_VIEW_NAME} DESTINATION lib)

set(VIEW_UNIT_TESTS view-unit-tests)

set(SOURCES_VIEW_UNIT_TESTS
    src/view.main.tests.cpp
    src/view.tests.cpp
)

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
