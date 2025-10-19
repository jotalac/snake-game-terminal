//
// Created by jotalac on 10/18/25.
//

#ifndef SNAKE_TEST_PLAYER_H
#define SNAKE_TEST_PLAYER_H
#include <string>
#include <vector>

class Snake {
private:
    int headX , headY;
    int x_vec = 1;
    int y_vec = 0;
    std::string direction = "RIGHT";
    std::string headSign;
    std::string bodySign;
    int length;
    std::vector<std::pair<int, int>> tailCoords = {};

public:
    Snake(int xPos, int yPos, const std::string &headSign = "@", const std::string &bodySign = "-", int length = 2);
    void moveTo(int xTo, int yTo);
    int getHeadX() const;
    int getHeadY() const;
    std::vector<std::pair<int, int>> getTailCoords() const;
    int getXVec() const;
    int getYVec() const;
    void setXVec(int new_vec);
    void setYVec(int new_vec);
    std::string getHeadSign() const;
    std::string getBodySign() const;
    void setDirection(std::string newDir);
    std::string getDirection();

    void updateTail();
    void updateHead();
};


#endif //SNAKE_TEST_PLAYER_H