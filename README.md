# search_engine

-> Описание проекта:
    Проект реализует поисковый движок для корпоративного портала.
    Программа ищет слова по набору текстовых документов и выдаёт наиболее релевантные результаты в формате JSON.

-> Особенности:
    Индексация документов в многопоточном режиме;
    Расчёт абсолютной и относительной релевантности документов;
    Настройка через config.json;
    Получение запросов через requests.json и запись результатов в answers.json;
    Полное соответствие техническому заданию Skillbox.

-> Структура проекта

ITBoxSearch/
├── CMakeLists.txt
├── src/
│ ├── ConverterJSON.cpp
│ ├── ConverterJSON.h
│ ├── InvertedIndex.cpp
│ ├── InvertedIndex.h
│ ├── SearchServer.cpp
│ ├── SearchServer.h
│ └── main.cpp
├── tests/
│ ├── test_inverted_index.cpp
│ └── test_search_server.cpp
├── external/
│ ├── nlohmann/json.hpp
│ └── googletest/
├── resources/
│ ├── file001.txt
│ └── file002.txt
├── config.json
├── requests.json
└── out/ (создаётся автоматически)

-> Сборка проекта

 1. Создать папку для сборки:
    ```bash
mkdir out
cd out
mkdir build
cd build

  2. Запустить CMake:
cmake ../..
cmake --build .
* Файлы ITBoxSearch.exe и runTests.exe появятся в out/build.

  3. Запуск
- Основной исполняемый файл:
./ITBoxSearch.exe

 - Тесты:
./runTests.exe


# Примечания
Папка out/ не заливается в GitHub, создаётся локально.
Все внешние зависимости находятся в external/ и уже включены в репозиторий.
config.json и requests.json автоматически создаются при сборке.
