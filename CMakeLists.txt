
cmake_minimum_required(VERSION 3.12)
project(http-server C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS 
    "src/*.c"
)

add_executable(http-server main.c ${SOURCES})
target_include_directories(http-server PRIVATE include)