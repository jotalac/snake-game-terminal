//
// Created by jotalac on 10/27/25.
//
#define CATCH_CONFIG_MAIN


#include "catch.hpp"
#include <cstdint>

#include "../entities/Snake.h"
#include "game/Game.h"

TEST_CASE("Snake constructor test", "[snake]") {
    const Snake snake(10, 5, "-", "*", 70);

    REQUIRE(snake.getHeadX() == 10);
    REQUIRE(snake.getHeadY() == 5);
    REQUIRE(snake.getHeadSign() == "--");
    REQUIRE(snake.getBodySign() == "**");
    REQUIRE(snake.getXVec() == 1);
    REQUIRE(snake.getYVec() == 0);
}

TEST_CASE("Snake move test", "[snake]") {
    Snake snake(20, 70);
    snake.updateHead();

    REQUIRE(snake.getHeadX() == 21);
    REQUIRE(snake.getHeadY() == 70);

    snake.setXVec(0);
    snake.setYVec(-1);
    snake.setDirection("DOWN");
    snake.updateHead();

    REQUIRE(snake.getHeadX() == 21);
    REQUIRE(snake.getHeadY() == 69);

    snake.moveTo(1, 1);
    REQUIRE(snake.getHeadX() == 1);
    REQUIRE(snake.getHeadY() == 1);

    REQUIRE_FALSE(snake.getDirection() == "LEFT");

}

TEST_CASE("Snake tail move test", "[snake]") {
    Snake snake(20, 70, "-", "-", 3);
    snake.updateTail();
    snake.updateHead();

    auto tailCoords = snake.getTailCoords();
    REQUIRE(tailCoords.size() == 2);
    REQUIRE(tailCoords[0].first == 20);
    REQUIRE(tailCoords[0].second == 70);

    snake.setXVec(0);
    snake.setYVec(1);
    snake.updateTail();
    snake.updateHead();
    tailCoords = snake.getTailCoords();

    REQUIRE(tailCoords[1].first == 20);
    REQUIRE(tailCoords[1].second == 70);
}

TEST_CASE("Game difficulty affects wall count", "[game]") {
    const Snake snake{5, 5, "▓", "@", 2};

    SECTION("Easy difficulty has fewer walls") {
        const Game easyGame{snake, true, 20, 20, 0};
        REQUIRE(easyGame.calculateWallNumber(true) <= 20*20/200);
    }

    SECTION("Hard difficulty has more walls") {
        Game hardGame{snake, true, 10, 10, 5};
        REQUIRE(hardGame.calculateWallNumber(true) > 10);
    }

    SECTION("No walls when disabled") {
        Game noWallsGame{snake, false, 20, 20, 3};
        REQUIRE(noWallsGame.calculateWallNumber(false) == 0);
    }
}
