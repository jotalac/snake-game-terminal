#include <iostream>
#include <thread>
#include <chrono>

#include "game/Game.h"
#include "entities/Snake.h"
#include "game/GameMenu.h"
#include "utils/constants.h"


int main() {
    srand(std::time(0));
    turnOnCbreak(); //enable 'raw' mode

    GameMenu game_menu;
    game_menu.gameLoop();

    turnOffCbreak();

    return 0;
}
