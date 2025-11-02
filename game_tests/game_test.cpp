//
// Created by jotalac on 10/27/25.
//
#define CATCH_CONFIG_MAIN


#include "catch.hpp"

#include "../entities/Snake.h"
#include "game/Game.h"
#include "game/GameMenu.h"

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

TEST_CASE("Item test spawn", "[item]") {
    Item item("**");

    REQUIRE(item.getSign() == "**");

    SECTION("Item respawns correctly") {
        int width = 10;
        int height = 10;
        item.respawnItem(width, height);

        REQUIRE(item.getX() >= 0);
        REQUIRE_FALSE(item.getX() > width);
        REQUIRE(item.getY() >= 0);
        REQUIRE_FALSE(item.getY() > height);
    }

    SECTION("Item spawn manually") {
        item.setX(51);
        item.setY(12);
        REQUIRE(item.getX() == 51);
        REQUIRE(item.getY() == 12);
    }
}

TEST_CASE("Game difficulty affects wall count", "[game]") {
    const Snake snake{5, 5, "▓", "@", 2};

    const int gameWidth = 20;
    const int gameHeight = 20;
    const int area = gameWidth * gameHeight;

    SECTION("Easy difficulty has fewer walls") {
        const Game easyGame{snake, true, gameWidth, gameHeight, 0};
        REQUIRE(easyGame.calculateWallNumber(true) <= area/200);
    }

    SECTION("Hard difficulty has more walls") {
        Game hardGame{snake, true, gameWidth, gameHeight, 5};
        REQUIRE(hardGame.calculateWallNumber(true) > area/200);
    }

    SECTION("No walls when disabled") {
        Game noWallsGame{snake, false, 20, 20, 3};
        REQUIRE(noWallsGame.calculateWallNumber(false) == 0);
    }
}

TEST_CASE("Game speed calculation", "[game]") {
    Snake snake{5, 5, "▓", "@", 2};
    Game game{snake, false, 20, 20, 2};

    SECTION("Game speed initial") {
        const auto initialSpeed = game.calculateGameSpeed();
        // Simulate score increase by playing
        REQUIRE(initialSpeed.count() == 120);
    }

    SECTION("Game speed increase with score") {

        const int score = 10;
        const double expectedSpeed = static_cast<int>(120 * (1 - (0.013 * score)));

        game.setScore(score);
        auto actualSpeed = game.calculateGameSpeed();
        REQUIRE(actualSpeed.count() == expectedSpeed);
    }
}

TEST_CASE("GameMenu settings management", "[menu]") {
    GameMenu menu;

    SECTION("Default game width is 25") {
        REQUIRE(menu.game_width() == 25);
    }

    SECTION("Default game height is 25") {
        REQUIRE(menu.game_height() == 25);
    }

    SECTION("Default difficulty is 2") {
        REQUIRE(menu.game_difficulty() == 2);
    }

    SECTION("Walls are enabled by default") {
        REQUIRE(menu.game_walls() == true);
    }
}

TEST_CASE("GameMenu settings modification", "[menu]") {
    GameMenu menu;

    SECTION("Can change game width") {
        menu.set_game_width(30);
        REQUIRE(menu.game_width() == 30);
    }

    SECTION("Can change game height") {
        menu.set_game_height(40);
        REQUIRE(menu.game_height() == 40);
    }

    SECTION("Can change difficulty") {
        menu.set_game_difficulty(4);
        REQUIRE(menu.game_difficulty() == 4);
    }

    SECTION("Can toggle walls") {
        menu.set_game_walls(false);
        REQUIRE(menu.game_walls() == false);
        menu.set_game_walls(true);
        REQUIRE(menu.game_walls() == true);
    }
}
