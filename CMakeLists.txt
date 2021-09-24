cmake_minimum_required(VERSION 3.12.4)
project(BigInteger)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_INSTALL_RPATH "${PROJECT_SOURCE_DIR}/bin")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()
add_executable(Test tests.cpp BigInteger.cpp)
add_test(Test ${PROJECT_SOURCE_DIR}/bin/testing)
target_link_libraries(Test Threads::Threads ${GTEST_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

add_executable(BigInteger main.cpp BigInteger.cpp)

set(CMAKE_EXE_LINKER_FLAGS --coverage)
add_definitions(-fprofile-arcs -ftest-coverage)
target_link_libraries(Test -fprofile-arcs)