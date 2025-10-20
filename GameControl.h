//
// Created by jotalac on 10/18/25.
//

#ifndef SNAKE_TEST_GAMEFIELD_H
#define SNAKE_TEST_GAMEFIELD_H

#include <bits/chrono.h>

#include "CollectItem.h"
#include "Snake.h"
#include "Walls.h"


class GameControl {
private:
    Snake snake;
    CollectItem itemCollect;
    int width;
    int height;
    bool gameRunning = true;
    int score = 0;

    Walls walls;

    // std::chrono::milliseconds delayMili = 110;
public:
    GameControl(int width, int height, const Snake& player, int numberOfWalls);
    bool isGameRunning() const;
    int getScore() const;

    std::chrono::milliseconds calculateGameSpeed(int difficulty) const;


    void printField() const;
    void printScore() const;
    void renderGame() const;
    void updatePlayerBounce();
    void updateSnake();
    static void cleanField();
    void controlSnake();
    void endGame() const;
};


#endif //SNAKE_TEST_GAMEFIELD_H