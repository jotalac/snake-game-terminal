//
// Created by jotalac on 10/18/25.
//

#ifndef SNAKE_TEST_GAMEFIELD_H
#define SNAKE_TEST_GAMEFIELD_H

#include <condition_variable>
#include <mutex>
#include <bits/chrono.h>

#include "../entities/CollectItem.h"
#include "../entities/Snake.h"
#include "../entities/Walls.h"


class Game {
private:
    Snake snake;
    CollectItem itemCollect;
    int width;
    int height;
    bool gameRunning = false;
    int score = 0;
    Walls walls;
    int difficulty;



    //threads
    std::thread computeThread;
    std::thread inputThread;
    std::thread renderThread;
    std::mutex mutex;
    std::condition_variable cvar;

    // std::chrono::milliseconds delayMili = 110;
public:
    Game(const Snake& player, bool showWalls = true, int width = 25, int height = 25, int difficulty = 4);

    Game(int width, int height, const Snake &player, int numberOfWalls);

    ~Game();
    bool isGameRunning() const;
    int getScore() const;

    std::chrono::milliseconds calculateGameSpeed() const;
    int calculateWallNumber(bool showWalls) const;

    void startGame();
    void stopGame();


private:
    void printField() const;
    void printScore() const;
    void renderGame() const;
    void updateSnake();

    // void controlSnake();
    void endScreen() const;
    void inputHandle(char intputChar);

    //threads actions
    void inputLoop();
    void computeLoop();
    void renderLoop();

};


#endif //SNAKE_TEST_GAMEFIELD_H