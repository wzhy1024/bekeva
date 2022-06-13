cmake_minimum_required(VERSION 3.22)
project(bekeva C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(bekeva src/main.c src/slot.c include/slot.h src/page.c include/page.h src/storage.c include/storage.h)
