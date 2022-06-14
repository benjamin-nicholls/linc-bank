cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(CMAKE_BUILD_TYPE Debug)

project(test)

#add_executable (LincBank LincBank.cpp)
#add_executable (historyinfo historyinfo.cpp)
#add_executable (savings savings.cpp)
#add_executable (current current.cpp)

add_executable (test LincBank.cpp transaction.cpp savings.cpp current.cpp mainmethods.cpp)