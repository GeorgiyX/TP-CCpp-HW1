set(EXE_NAME TP-TESTING-HW1)
set(TEST_SEED 777)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} include)

add_executable(${EXE_NAME} src/main.cpp ${HW_SRC}
               src/io_tests.cpp src/utils.cpp src/managements_tests.cpp)
target_link_libraries(${EXE_NAME} ${GTEST_BOTH_LIBRARIES} pthread)

add_test(NAME MainTest COMMAND ${EXE_NAME} ../ ${TEST_SEED})
