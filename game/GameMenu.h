//
// Created by jotalac on 22.10.25.
//

#ifndef SNEJKS_GAMEMENU_H
#define SNEJKS_GAMEMENU_H
#include "Game.h"


class GameMenu {
private:
    // game settings variables
    int gameWidth = 25;
    int gameHeight = 25;
    int gameDifficulty = 2;
    bool gameWalls = true;

public:
    GameMenu();
    // void startNewGame();

    bool showMenu();
    void showSettings();
    void gameLoop();
    void startGame();

    //getters and setters
    int game_width() const {
        return gameWidth;
    }

    void set_game_width(int game_width) {
        gameWidth = game_width;
    }

    int game_height() const {
        return gameHeight;
    }

    void set_game_height(int game_height) {
        gameHeight = game_height;
    }

    int game_difficulty() const {
        return gameDifficulty;
    }

    void set_game_difficulty(int game_difficulty) {
        gameDifficulty = game_difficulty;
    }

    bool game_walls() const {
        return gameWalls;
    }

    void set_game_walls(bool game_walls) {
        gameWalls = game_walls;
    }
};


#endif //SNEJKS_GAMEMENU_H