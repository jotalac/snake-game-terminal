//
// Created by jotalac on 22.10.25.
//

#ifndef SNEJKS_GAMEMENU_H
#define SNEJKS_GAMEMENU_H
#include "Game.h"


class GameMenu {
private:
    std::unique_ptr<Game> game;
public:
    GameMenu();
    // void startNewGame();

    bool showMenu();
    void gameStartup();
};


#endif //SNEJKS_GAMEMENU_H