

include_directories(${PROJECT_SOURCE_DIR})

set(HEADER_FILES
    model.h
)

set(SOURCE_FILES
    model.cpp
)

set(TARGET_MODEL_NAME lovely_model)
set(LIBRARY_MODEL_NAME ${TARGET_MODEL_NAME} PARENT_SCOPE)

add_library(${TARGET_MODEL_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${TARGET_MODEL_NAME} PUBLIC .)
target_compile_features(${TARGET_MODEL_NAME} PUBLIC cxx_std_17)

set(MODEL_UNIT_TESTS model-unit-tests)

set(SOURCES_MODEL_UNIT_TESTS
    model.main.tests.cpp
    model.tests.cpp
)

include_directories(${CATCH2_INCLUDE_DIRECTORY})

add_executable(${MODEL_UNIT_TESTS} ${SOURCES_MODEL_UNIT_TESTS})
target_compile_features(${MODEL_UNIT_TESTS} PRIVATE cxx_std_17)
target_link_libraries(${MODEL_UNIT_TESTS} PRIVATE ${TARGET_MODEL_NAME})

set(RUN_TEST_AFTER_BUILD true)

if (RUN_TEST_AFTER_BUILD)
    add_custom_command(
        TARGET ${MODEL_UNIT_TESTS}
        COMMENT "run model tests"
        POST_BUILD
        COMMAND ${MODEL_UNIT_TESTS} ~long:*
    )
endif()
