#include <iostream>
#include <thread>
#include <chrono>

#include "game/Game.h"
#include "entities/Snake.h"
#include "game/GameMenu.h"


int main() {
    srand(std::time(0));

    // const Snake snake{1, 1, "▓", "@", 2};
    // Game game_field{30, 30, snake, 10};
    GameMenu game_menu;

    game_menu.showMenu();

    // game_menu.startNewGame();

    // game_field.startGame();
    //
    // // // Wait for game to finish
    // while (game_field.isGameRunning()) {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(300));
    // }

    return 0;
}
