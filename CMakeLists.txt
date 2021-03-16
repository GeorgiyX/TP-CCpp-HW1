cmake_minimum_required(VERSION 3.17)
project(TP-HW1 C)

set(CMAKE_C_STANDARD 11)
add_compile_definitions(_POSIX_C_SOURCE _GNU_SOURCE  _TESTING)

include_directories(project/include)

add_executable(${PROJECT_NAME} project/src/main.c project/include/list_managment.h project/src/list_managment.c project/include/io_list_operations.h project/src/io_list_operations.c)