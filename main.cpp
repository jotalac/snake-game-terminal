#include <iostream>
#include <thread>
#include <chrono>

#include "GameControl.h"
#include "Snake.h"




int main() {
    srand(std::time(0));
    const Snake snake(1, 1, "▓", "@", 2);
    GameControl game_field(30, 30, snake, 20);

    while (game_field.isGameRunning()) {
        game_field.controlSnake();
        game_field.updateSnake();
        game_field.renderGame();
        std::this_thread::sleep_for(game_field.calculateGameSpeed(2)); //sleep for while
    }

    game_field.endGame();

    return 0;
}

