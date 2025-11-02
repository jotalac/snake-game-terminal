cmake_minimum_required(VERSION 4.0)
project(snejks)

set(CMAKE_CXX_STANDARD 20)

set(GAME_SOURCES
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

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/game_tests
)

add_executable(snejks main.cpp ${GAME_SOURCES})

# executable for the tests
add_executable(game-test-runner
        game_tests/game_test.cpp
        game_tests/catch.cpp
        ${GAME_SOURCES}
)

#copy the resources to the build directory
file(COPY res/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res)

enable_testing()
add_test(NAME game-test COMMAND game-test-runner)
