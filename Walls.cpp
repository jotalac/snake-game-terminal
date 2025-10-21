//
// Created by jotalac on 10/20/25.
//

#include "Walls.h"

#include <iostream>

Walls::Walls(const int numberOfWalls, const std::string &sign): sign(sign) {
    for (int i = 0; i < numberOfWalls; i++) {
        wallItems.push_back(Item(sign));
    }
}

//
// void Walls::placeSingleWall(int gameWidth, int gameHeight, int snakeX, int snakeY) {
// }


void Walls::placeWalls(const int gameWidth, const int gameHeight, const int snakeX, const int snakeY) {
    for (Item& item : wallItems) {
        do {
            item.respawnItem(gameWidth, gameHeight);
        } while (abs(item.getX() - snakeX) < 3 && abs(item.getY() - snakeY) < 3);
    }
}

std::vector<std::pair<int, int> > Walls::getWallPositions() const {
    std::vector<std::pair<int, int>> returnValues = {};
    for (const auto& wall : wallItems) {
        returnValues.push_back({wall.getX(), wall.getY()});
    }

    return returnValues;
}

std::string Walls::getSign() const {
    return sign;
}


