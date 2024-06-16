# Data Structure and Algorithm Benchmarking

## Описание

Этот проект предназначен для тестирования производительности пользовательских структур данных и алгоритмов с использованием OpenMP для параллельного выполнения. Программа компилирует динамическую библиотеку из указанного файла со структурой данных и алгоритмом, и выполняет его, измеряя среднее время выполнения при различных количествах потоков.

## Структура проекта

- `src/` - Директория с исходными файлами.
- `include/` - Директория с заголовочными файлами.
- `build/` - Директория для промежуточных файлов сборки.
- `bin/` - Директория для исполняемых файлов и динамических библиотек.
- `CMakeLists.txt` - CMake файл для сборки проекта.
- `README.md` - Этот файл.

## Требования

- C++ компилятор с поддержкой OpenMP (например, g++)
- CMake (минимальная версия 3.10)
- Git (для клонирования репозитория)

## Сборка и запуск

### Сборка проекта

1. Клонируйте репозиторий:

    ```bash
    git clone https://github.com/rezy-maks/VKR.git
    cd VKR
    ```

2. Создайте папку `build` и перейдите в нее:

    ```bash
    mkdir build
    cd build
    ```

3. Запустите CMake для настройки проекта:

    ```bash
    cmake ..
    ```

4. Скомпилируйте проект с помощью `make`:

    ```bash
    make
    ```

### Запуск программы

1. Перейдите в директорию `VKR`:

    ```bash
    cd ..
    ```

2. Запустите программу, указав файл со структурой данных и алгоритмом:

    ```bash
    ./bin/main_program path_to_your_data_structure_and_algorithm_file.cpp
    ```

    Убедитесь, что указанный файл содержит реализацию структуры данных и алгоритма.

## Пример реализации структуры данных

1. Пример реализации структуры данных и алгоритма представлен в файле `src/my_data_structure.cpp`

2. Запуститm программу, используя данную структуру данных и алгоритм можно с помощью команды:

    ```bash
    ./bin/main_program ./src/my_data_structure.cpp
    ```