//
// Created by jotalac on 22.10.25.
//

#ifndef SNEJKS_GAMEMENU_H
#define SNEJKS_GAMEMENU_H
#include "GameControl.h"


class GameMenu {
private:
    GameControl game_control;
public:
    GameMenu(GameControl game_control);

    void startGame();
};


#endif //SNEJKS_GAMEMENU_H