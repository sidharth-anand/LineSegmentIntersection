cmake_minimum_required(VERSION 3.10)

project(LineIntersection)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED True)

option (USE_STRUCTURES ON)

set (EXTRA_LIBS "")
set (EXTRA_INCLUDES "")

add_subdirectory (structures)
list (APPEND EXTRA_LIBS structures)

add_executable(LineIntersection main/main.cpp)

target_link_libraries(LineIntersection PUBLIC ${EXTRA_LIBS})
target_include_directories(LineIntersection PUBLIC "${PROJECT_BINARY_FILE}")

install (TARGETS LineIntersection DESTINATION bin)