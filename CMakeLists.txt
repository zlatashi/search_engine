cmake_minimum_required(VERSION 3.16)
project(ITBoxSearch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути
set(NLOHMANN_DIR ${CMAKE_SOURCE_DIR}/external/nlohmann)
set(GTEST_DIR ${CMAKE_SOURCE_DIR}/external/googletest)

# Исходники проекта
set(PROJECT_SOURCES
    src/InvertedIndex.cpp
    src/SearchServer.cpp
    src/ConverterJSON.cpp
    src/main.cpp
)

# Тесты
set(TEST_SOURCES
    tests/test_inverted_index.cpp
    tests/test_search_server.cpp
)

# Основной проект
add_executable(ITBoxSearch ${PROJECT_SOURCES})
target_include_directories(ITBoxSearch PRIVATE src ${NLOHMANN_DIR})

# Подключаем GoogleTest как подпроект
add_subdirectory(${GTEST_DIR} googletest_build)

# Тестовый исполняемый файл
add_executable(runTests ${PROJECT_SOURCES} ${TEST_SOURCES})
target_include_directories(runTests PRIVATE src ${NLOHMANN_DIR})
target_link_libraries(runTests gtest gtest_main gmock)
