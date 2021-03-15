cmake_minimum_required(VERSION 3.17)
project(TP-TESTING-HW1 CXX)
set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(_POSIX_C_SOURCE _GNU_SOURCE  _TESTING)
find_package(GTest REQUIRED)
include_directories("${GTEST_INCLUDE_DIRS}"
                     testing/include)

add_executable(${PROJECT_NAME} testing/src/main.c)

target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
enable_testing()