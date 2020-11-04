# CMakeList.txt: проект CMake для linear; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (linear "linear.cpp" "linear.h" "matrix.h" "matrix.cpp" "var.h" "complex.h" "complex.cpp" "vector.h" "vector.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
