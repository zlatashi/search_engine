# Search Engine Project

Компактный многопоточный поисковый движок на C++17 с поддержкой JSON и ранжированием результатов.

## Технологии
- C++17
- Google Test
- nlohmann/json (JSON for Modern C++)

## Структура проекта
search_engine/
├─ CMakeLists.txt # Главный CMake
├─ config/
│ ├─ config.json # Настройки и список файлов для поиска
│ ├─ requests.json # Запросы для поиска
│ └─ answers.json # Результаты поиска
├─ include/
│ ├─ converter_json.h
│ ├─ inverted_index.h
│ └─ search_server.h
├─ src/
│ ├─ converter_json.cpp
│ ├─ inverted_index.cpp
│ ├─ search_server.cpp
│ └─ main.cpp
├─ tests/
│ ├─ CMakeLists.txt
│ ├─ test_index.cpp
│ └─ test_server.cpp
└─ resources/
├─ file001.txt
├─ file002.txt
├─ file003.txt
└─ file004.txt

bash
Копировать код

## Сборка и запуск
```bash
mkdir build
cd build
cmake ..
cmake --build .
./search_server
Особенности
Многопоточность: параллельная обработка запросов через std::async.

Защита данных: InvertedIndex использует std::mutex для безопасного доступа.

Обработка JSON: проверка открытия файлов и синтаксиса с информативными исключениями.

Ранжирование: результаты сортируются по релевантности, ограничено max_responses.


