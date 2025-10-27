cmake_minimum_required(VERSION 4.0)
project(snejks)

set(CMAKE_CXX_STANDARD 20)

add_executable(snejks main.cpp
        entities/Snake.cpp
        entities/Snake.h
        game/Game.cpp
        game/Game.h
        utils/FilePrinter.cpp
        utils/FilePrinter.h
        entities/CollectItem.cpp
        entities/CollectItem.h
        entities/Item.cpp
        entities/Item.h
        entities/Walls.cpp
        entities/Walls.h
        game/GameMenu.h
        game/GameMenu.cpp
        utils/constants.h
)
