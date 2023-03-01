cmake_minimum_required(VERSION 3.22)
project(ThinkgearSimple VERSION 1.0.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 11)

FILE(GLOB HEADERS *.h)

# 1
# FILE(GLOB SOURCES *.cpp )
# 2
FILE(GLOB SOURCES *.c *.cpp)



include_directories(./)

add_executable(
    ${PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
    )
