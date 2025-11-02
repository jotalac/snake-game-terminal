//
// Created by jotalac on 10/20/25.
//

#ifndef SNAKE_TEST_WALLITEM_H
#define SNAKE_TEST_WALLITEM_H
#include <string>
#include <vector>

#include "Item.h"


class Walls{
private:
    std::vector<Item> wallItems;
    std::string sign;
public:
    Walls(int numberOfWalls, const std::string& sign);
    void placeWalls(int gameWidth, int gameHeight, int snakeX, int snakeY);

    std::string getSign() const;

    std::vector<std::pair<int, int>> getWallPositions() const;
};


#endif //SNAKE_TEST_WALLITEM_H