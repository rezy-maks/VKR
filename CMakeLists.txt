cmake_minimum_required(VERSION 3.10)

# Название проекта
project(VKR LANGUAGES CXX)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Включение поддержки OpenMP
find_package(OpenMP REQUIRED)

# Пути к исходным и заголовочным файлам
include_directories(include)
set(SRC_DIR src)

# Добавление исходных файлов
set(SOURCES
    ${SRC_DIR}/main.cpp
)

# Добавление файлов для создания динамической библиотеки
set(LIBRARY_SOURCES
    ${SRC_DIR}/my_data_structure.cpp
)

# Создание исполняемого файла
add_executable(main_program ${SOURCES})

# Создание динамической библиотеки
add_library(data SHARED ${LIBRARY_SOURCES})

# Линковка с библиотеками
target_link_libraries(main_program PRIVATE data OpenMP::OpenMP_CXX)
target_link_libraries(data PRIVATE OpenMP::OpenMP_CXX)

# Установка выходных директорий для бинарных файлов и библиотек
set_target_properties(main_program PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin
)
set_target_properties(data PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin
)

# Включение всех предупреждений
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(main_program PRIVATE -Wall -Wextra -O2)
    target_compile_options(data PRIVATE -Wall -Wextra -O2)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(main_program PRIVATE /W4 /O2)
    target_compile_options(data PRIVATE /W4 /O2)
endif()
