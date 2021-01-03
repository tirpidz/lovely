include_directories(${PROJECT_SOURCE_DIR})

set(MAIN main)

set(HEADER_FILES
    version.h
)

add_library(lovely_version ${HEADER_FILES})
set_target_properties(lovely_version PROPERTIES LINKER_LANGUAGE CXX)

set(SOURCES_MAIN
    main.cpp
)

add_executable(${MAIN} ${SOURCES_MAIN})
target_compile_features(${MAIN} PRIVATE cxx_std_17)
target_link_libraries(${MAIN} PRIVATE lovely_api)
# target_link_libraries(${MAIN} PRIVATE lovely_external_imgui)
target_link_libraries(${MAIN} PRIVATE lovely_fetch)
target_link_libraries(${MAIN} PRIVATE lovely_window)
target_link_libraries(${MAIN} PRIVATE lovely_version)
