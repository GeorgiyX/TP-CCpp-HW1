cmake_minimum_required(VERSION 3.12.4)
project(TP-HW1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
# code coverage:
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -g ")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
set(PROJECT_DIR ${CMAKE_SOURCE_DIR}/project)
add_compile_definitions(_POSIX_C_SOURCE _GNU_SOURCE _TESTING)

include_directories(project/include)
set(HW_SRC ${PROJECT_DIR}/include/list_management.h
           ${PROJECT_DIR}/src/list_management.c
           ${PROJECT_DIR}/include/io_list_operations.h
           ${PROJECT_DIR}/src/io_list_operations.c)
add_executable(${PROJECT_NAME} project/src/main.c ${HW_SRC})

enable_testing()
add_subdirectory(project/testing)
