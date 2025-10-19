//
// Created by jotalac on 10/18/25.
//

#ifndef SNAKE_TEST_GAMEFIELD_H
#define SNAKE_TEST_GAMEFIELD_H

#include "Snake.h"


class GameControl {
private:
    Snake snake;
    int width;
    int height;
    bool gameRunning = true;
public:
    GameControl(int width, int height, const Snake& player);
    bool isGameRunning() const;

    void printField() const;
    void updatePlayerBounce();
    void updateSnake();
    static void cleanField();
    void controlSnake();
    void endGame();
};


#endif //SNAKE_TEST_GAMEFIELD_H