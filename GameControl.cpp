#include "GameControl.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <termio.h>
// #include <bits/fs_path.h>

#include "kbhit.h"
#include "FilePrinter.h"


GameControl::GameControl(const int width, const int height, const Snake& player, const int numberOfWalls)
    : snake(player), itemCollect("**"), width(width), height(height), walls(numberOfWalls, "▓▓") {
    itemCollect.respawnItem(width, height);
    walls.placeWalls(width, height);
}

void GameControl::cleanField() {
    std::cout << "\033[2J\033[H";
}

bool GameControl::isGameRunning() const {
    return gameRunning;
}

int GameControl::getScore() const {
    return score;
}

std::chrono::milliseconds GameControl::calculateGameSpeed(const int difficulty) const {
    int minDelay = 20;
    int initDelay = 110;
    double decrease;
    switch (difficulty) {
        case 0:
            initDelay = 400;
            decrease = 0.001;
        case 1:
            decrease = 0.01;
            break;
        case 2:
            decrease = 0.02;
            break;
        case 3:
            decrease = 0.04;
            break;
        case 4:
            decrease = 0.1;
            break;
        default:
            decrease = 0.02;
    }
    return std::chrono::milliseconds(std::max(static_cast<int>(initDelay * (1 - (decrease * score))), minDelay));
}




void GameControl::updatePlayerBounce() {
    //update player position
    const int playerX = snake.getHeadX();
    const int playerY = snake.getHeadY();

    snake.setXVec(playerX >= width || playerX <= 0 ? snake.getXVec() * -1 : snake.getXVec());
    snake.setYVec(playerY >= height || playerY <= 0 ? snake.getYVec() * -1 : snake.getYVec());

    snake.moveTo(playerX + snake.getXVec(), playerY + snake.getYVec());
}

void GameControl::updateSnake() {
    const int headX = snake.getHeadX();
    const int headY = snake.getHeadY();
    std::vector<std::pair<int, int>> tail = snake.getTailCoords();
    std::vector<std::pair<int, int>> wallPositions = walls.getWallPositions();

    //check colision with boundary
    if (headX > width || headX < 0 || headY > height || headY < 0) {
        gameRunning = false;
        return;
    }
    //check or colision head with tail
    if ((std::ranges::find(tail, std::make_pair(headX, headY)) != tail.end())) {
        gameRunning = false;
        return;
    }

    //check item collect
    if (headX == itemCollect.getX() && headY == itemCollect.getY()) {
        snake.incrementSize();
        itemCollect.respawnItem(width, height);
        walls.placeWalls(width, height);
        score++;
        return;
    }

    //check collision with wall obsticle
    if ((std::ranges::find(wallPositions, std::make_pair(headX, headY)) != wallPositions.end())) {
        gameRunning = false;
        return;
    }

    //update snake positions
    snake.updateTail();
    snake.updateHead();
    itemCollect.moveRand(width, height);
}

void GameControl::controlSnake() {
    if (kbhit()) {
        switch (getchar()) {
            case 'w':
                if (snake.getDirection() != "DOWN") {
                    snake.setDirection("UP");
                    snake.setXVec(0);
                    snake.setYVec(-1);
                }
                break;
            case 'a':
                if (snake.getDirection() != "RIGHT") {
                    snake.setDirection("LEFT");
                    snake.setXVec(-1);
                    snake.setYVec(0);
                }
                break;
            case 's':
                if (snake.getDirection() != "UP") {
                    snake.setDirection("DOWN");
                    snake.setXVec(0);
                    snake.setYVec(1);
                }
                break;
            case 'd':
                if (snake.getDirection() != "LEFT") {
                    snake.setDirection("RIGHT");
                    snake.setXVec(1);
                    snake.setYVec(0);
                }
                break;
            default:
                break;
        }
    }
}

void GameControl::endGame() const {
    cleanField();
    FilePrinter::printFile("../resources/game_over.txt");

    //print the numbers of score
    std::string scoreText = std::string("===============") + " Your score: " + std::to_string(score) + " ===============";

    std::cout << scoreText << std::endl;
}


void GameControl::printField() const {
    std::vector<std::pair<int, int>> tail = snake.getTailCoords();
    std::vector<std::pair<int, int>> wallPositions = walls.getWallPositions();

    //print the outline
    std::cout << std::setfill('=') << std::setw(width*2+2) << "" << std::endl;
    //print the sides
    for (int row = 0; row < height; ++row) {
        std::cout << "║";

        for (int col = 0; col < width; ++col) {
            //check if to print the head
            if (snake.getHeadX() == col && snake.getHeadY() == row) std::cout << "\033[33m" <<  snake.getHeadSign() << "\033[0m";
            //check if to print he tail
            else if (std::ranges::find(tail, std::make_pair(col, row)) != tail.end()) {
                std::cout << "\033[32m" << snake.getBodySign() << "\033[0m";
            }
            //print the collectable item
            else if (itemCollect.getX() == col && itemCollect.getY() == row) {
                std::cout << "\033[35m" << itemCollect.getSign() << "\033[0m";
            }
            //print the wall obsticle
            else if (std::ranges::find(wallPositions, std::make_pair(col, row)) != wallPositions.end()) {
                std::cout << "\x1b[91m" << walls.getSign() << "\033[0m";
            }

            //print the background
            // else std::cout << "\033[0m░░";
            else std::cout << "\033[0m  ";
        }
        // std::cout << std::setfill(' ') << std::setw(width) << "";
        std::cout << "║" << std::endl;
    }
    //print the final line
    std::cout << std::setfill('=') << std::setw(width*2 + 2) << "" << std::endl;
    // printScore();

}

void GameControl::printScore() const {

    std::string text = " Your score: " + std::to_string(score) + " ";
    std::string padding = std::string(width - text.length() / 2, ' ');

    std::cout << std::setfill('=') << std::setw(width*2+2) << "" << std::endl;
    std::cout << "\033[1;31m" << padding << text << padding << "\033[0m" << std::endl;
    std::cout << std::setfill('=') << std::setw(width*2+2) << "" << std::endl;
    // std::cout << (width - text.length());
}

void GameControl::renderGame() const {
    cleanField();
    printField();
    printScore();
}
