#include <iostream>
#include <thread>
#include <chrono>

#include "GameControl.h"
#include "Snake.h"




int main() {
    const Snake snake(10, 10, "▓", "@", 20);
    GameControl game_field(30, 30, snake);

    while (game_field.isGameRunning()) {
        game_field.controlSnake();
        game_field.updateSnake();
        game_field.printField();
        std::this_thread::sleep_for(std::chrono::milliseconds(60)); //sleep for while
    }

    game_field.endGame();

    return 0;
}

