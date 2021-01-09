include_directories(${PROJECT_SOURCE_DIR})
include_directories(${CATCH2_INCLUDE_DIRECTORY})

set(HEADER_FILES
    view.h
)

set(SOURCE_FILES
    view.cpp
)

set(TARGET_VIEW_NAME lovely_view)
set(LIBRARY_VIEW_NAME ${TARGET_VIEW_NAME} PARENT_SCOPE)

add_library(${TARGET_VIEW_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${TARGET_VIEW_NAME} PUBLIC .)
target_compile_features(${TARGET_VIEW_NAME} PUBLIC cxx_std_17)
target_link_libraries(${TARGET_VIEW_NAME} PRIVATE ${LIBRARY_CONTROLLER_NAME})
target_link_libraries(${TARGET_VIEW_NAME} PRIVATE ${LIBRARY_MODEL_NAME})

set(VIEW_UNIT_TESTS view-unit-tests)

set(SOURCES_VIEW_UNIT_TESTS
    view.main.tests.cpp
    view.tests.cpp
)

add_executable(${VIEW_UNIT_TESTS} ${SOURCES_VIEW_UNIT_TESTS})
target_compile_features(${VIEW_UNIT_TESTS} PRIVATE cxx_std_17)
target_link_libraries(${VIEW_UNIT_TESTS} PRIVATE ${TARGET_VIEW_NAME})

set(RUN_TEST_AFTER_BUILD true)

if (RUN_TEST_AFTER_BUILD)
    add_custom_command(
        TARGET ${VIEW_UNIT_TESTS}
        COMMENT "run view tests"
        POST_BUILD
        COMMAND ${VIEW_UNIT_TESTS} ~long:*
    )
endif()
