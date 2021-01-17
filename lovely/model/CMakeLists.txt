set(HEADER_FILES
    include/lovely/model/model.h
    include/lovely/model/registry.h
    include/lovely/model/symbol/etf.h
    include/lovely/model/symbol/stock.h
    include/lovely/model/symbol/symbol.h
)

set(SOURCE_FILES
    src/model.cpp
)

set(TARGET_MODEL_NAME lovely_model)

add_library(${TARGET_MODEL_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${TARGET_MODEL_NAME} PUBLIC include)
target_compile_features(${TARGET_MODEL_NAME} PUBLIC cxx_std_17)
install(TARGETS ${TARGET_MODEL_NAME} DESTINATION lib)

set(MODEL_UNIT_TESTS model-unit-tests)

set(SOURCES_MODEL_UNIT_TESTS
    src/model.main.tests.cpp
    src/model.tests.cpp
    src/registry.tests.cpp
)

add_executable(${MODEL_UNIT_TESTS} ${SOURCES_MODEL_UNIT_TESTS})
target_compile_features(${MODEL_UNIT_TESTS} PRIVATE cxx_std_17)
target_link_libraries(${MODEL_UNIT_TESTS} PRIVATE ${TARGET_MODEL_NAME})
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
