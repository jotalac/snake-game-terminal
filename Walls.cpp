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

void Walls::placeWalls(const int gameWidth, const int gameHeight) {
    for (Item& item : wallItems) {
        item.respawnItem(gameWidth, gameHeight);
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


