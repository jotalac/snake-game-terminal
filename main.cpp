#include <iostream>
#include <thread>
#include <chrono>

#include "game/Game.h"
#include "entities/Snake.h"
#include "game/GameMenu.h"


int main() {
    srand(std::time(0));
    GameMenu game_menu;
    game_menu.gameLoop();
    return 0;
}
