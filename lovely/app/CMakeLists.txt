include_directories(${PROJECT_SOURCE_DIR})

set(MAIN main)

set(HEADER_FILES
    version.h
)

set(LIBRARY_CONTROLLER_NAME lovely_controller)
set(LIBRARY_MODEL_NAME lovely_model)
set(LIBRARY_VERSION_NAME lovely_version)
set(LIBRARY_VIEW_NAME lovely_view)

add_library(${LIBRARY_VERSION_NAME} ${HEADER_FILES})
set_target_properties(${LIBRARY_VERSION_NAME} PROPERTIES LINKER_LANGUAGE CXX)

set(SOURCES_MAIN
    main.cpp
)

add_executable(${MAIN} ${SOURCES_MAIN})
target_compile_features(${MAIN} PRIVATE cxx_std_17)
target_link_libraries(${MAIN} PRIVATE ${LIBRARY_CONTROLLER_NAME})
target_link_libraries(${MAIN} PRIVATE ${LIBRARY_MODEL_NAME})
target_link_libraries(${MAIN} PRIVATE ${LIBRARY_VIEW_NAME})
target_link_libraries(${MAIN} PRIVATE ${LIBRARY_VERSION_NAME})
