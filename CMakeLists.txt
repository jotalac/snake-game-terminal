cmake_minimum_required(VERSION 4.0)
project(snake_test)

set(CMAKE_CXX_STANDARD 20)

add_executable(snake_test main.cpp
        Snake.cpp
        Snake.h
        GameControl.cpp
        GameControl.h
        kbhit.cpp
        kbhit.h
        FilePrinter.cpp
        FilePrinter.h
        CollectItem.cpp
        CollectItem.h
        Item.cpp
        Item.h
        Walls.cpp
        Walls.h
)
