cmake_minimum_required(VERSION 3.16)

# Имя проекта 
project(MatrixIO CXX)

# стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # без gnu++ расширений, выглядит аккуратнее

# Создаём исполняемый файл из main.cpp
add_executable(matrix_app
    matrix_main/main.cpp
)

# Говорим где лежат заголовочные файлы
target_include_directories(matrix_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/header
)