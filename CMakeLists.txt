cmake_minimum_required(VERSION 3.16)
project(ITBoxSearch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NLOHMANN_DIR ${CMAKE_SOURCE_DIR}/external/nlohmann)
set(GTEST_DIR ${CMAKE_SOURCE_DIR}/external/googletest)

set(PROJECT_SOURCES
    src/InvertedIndex.cpp
    src/SearchServer.cpp
    src/ConverterJSON.cpp
    src/main.cpp
)

set(TEST_SOURCES
    tests/test_inverted_index.cpp
    tests/test_search_server.cpp
)

add_executable(ITBoxSearch ${PROJECT_SOURCES})
target_include_directories(ITBoxSearch PRIVATE src ${NLOHMANN_DIR})

add_subdirectory(${GTEST_DIR} googletest_build)

add_executable(runTests ${PROJECT_SOURCES} ${TEST_SOURCES})
target_include_directories(runTests PRIVATE src ${NLOHMANN_DIR})
target_link_libraries(runTests gtest gtest_main gmock)

set(RESOURCES_DIR "${CMAKE_SOURCE_DIR}/resources")
set(JSON_FILES "${CMAKE_SOURCE_DIR}/config.json" "${CMAKE_SOURCE_DIR}/requests.json")

if (CMAKE_CONFIGURATION_TYPES) # Multi-config (Visual Studio)
    set(RUNTIME_OUTPUT_DIR "${CMAKE_BINARY_DIR}/$<CONFIG>") 
else()
    set(RUNTIME_OUTPUT_DIR "${CMAKE_BINARY_DIR}")
endif()

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${RUNTIME_OUTPUT_DIR}/resources"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${RESOURCES_DIR}" "${RUNTIME_OUTPUT_DIR}/resources"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${JSON_FILES} "${RUNTIME_OUTPUT_DIR}"
    BYPRODUCTS "${RUNTIME_OUTPUT_DIR}/resources" "${RUNTIME_OUTPUT_DIR}/config.json" "${RUNTIME_OUTPUT_DIR}/requests.json"
    COMMENT "Copying resources and JSON files to ${RUNTIME_OUTPUT_DIR}"
)

add_dependencies(ITBoxSearch copy_resources)
add_dependencies(runTests copy_resources)
