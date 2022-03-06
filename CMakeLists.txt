cmake_minimum_required(VERSION 3.10)

project(LineIntersection)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED True)

set (EXTRA_LIBS "")
set (EXTRA_INCLUDES "")

add_subdirectory (structures)
add_subdirectory (geometry)

list (APPEND EXTRA_LIBS structures)
list (APPEND EXTRA_LIBS geometry)

add_executable(LineIntersection main/main.cpp)

target_link_libraries(LineIntersection PUBLIC ${EXTRA_LIBS})
target_include_directories(LineIntersection PUBLIC "${PROJECT_BINARY_FILE}")

install (TARGETS LineIntersection DESTINATION bin)