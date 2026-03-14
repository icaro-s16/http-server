cmake_minimum_required(VERSION 3.10)
project(http-server C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE SOURCES 
    "src/*.c"
)

add_executable(http-server main.c ${SOURCES})

