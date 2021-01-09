include_directories(${PROJECT_SOURCE_DIR})

set(HEADER_FILES
    view.h
)

set(SOURCE_FILES
    view.cpp
)

set(LIBRARY_CONTROLLER_NAME lovely_controller)
set(LIBRARY_MODEL_NAME lovely_model)
set(LIBRARY_VIEW_NAME lovely_view)

add_library(${LIBRARY_VIEW_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${LIBRARY_VIEW_NAME} PUBLIC .)
target_compile_features(${LIBRARY_VIEW_NAME} PUBLIC cxx_std_17)
target_link_libraries(${LIBRARY_VIEW_NAME} PRIVATE ${LIBRARY_CONTROLLER_NAME})
target_link_libraries(${LIBRARY_VIEW_NAME} PRIVATE ${LIBRARY_MODEL_NAME})

set(VIEW_UNIT_TESTS view-unit-tests)

set(SOURCES_VIEW_UNIT_TESTS
    view.main.tests.cpp
    view.tests.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/lovely/external/catch2/single_include)

add_executable(${VIEW_UNIT_TESTS} ${SOURCES_VIEW_UNIT_TESTS})
target_compile_features(${VIEW_UNIT_TESTS} PRIVATE cxx_std_17)
target_link_libraries(${VIEW_UNIT_TESTS} PRIVATE ${LIBRARY_VIEW_NAME})

set(RUN_TEST_AFTER_BUILD true)

if (RUN_TEST_AFTER_BUILD)
    add_custom_command(
        TARGET ${VIEW_UNIT_TESTS}
        COMMENT "run view tests"
        POST_BUILD
        COMMAND ${VIEW_UNIT_TESTS} ~long:*
    )
endif()
