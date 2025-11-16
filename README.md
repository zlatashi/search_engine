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
search_engine/
├── src/                  # исходники (.cpp и .h)
├── tests/                # юнит-тесты с Google Test
├── external/             # библиотеки для JSON и GTest
├── CMakeLists.txt        # основной CMake
├── README.md             # этот файл
└── out/                  # папка сборки
    └── build-x64-Debug/  # здесь создается исполняемый файл
        ├── search_engine.exe
        ├── config.json
        ├── requests.json
        ├── answers.json   # создаётся программой автоматически
        └── resources/    # текстовые файлы для поиска
            ├── file001.txt
            ├── file002.txt
            └── …

-> Настройка и запуск
   1. Клонируйте репозиторий:
git clone https://github.com/username/repo_name.git
cd repo_name

   2. Создайте папку сборки:
mkdir -p out/build-x64-Debug
cd out/build-x64-Debug

   3. Скопируйте в эту папку папку resources и файлы config.json, requests.json из репозитория:
cp -r ../../../resources .
cp ../../../config.json .
cp ../../../requests.json .

   4. Соберите проект с помощью CMake:
cmake ../../..
cmake --build . --config Debug

   5. Запустите программу:
./search_engine

   6. После работы в папке появится answers.json с результатами поиска.
