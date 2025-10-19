//
// Created by jotalac on 10/19/25.
//
#include "CollectItem.h"

#include <ctime>
#include <random>

int CollectItem::getX() const {
    return x;
}

int CollectItem::getY() const {
    return y;
}

void CollectItem::respawnItem(const int gameWidth, const int gameHeight) {
    srand(std::time(0));

    x = rand() % (gameWidth);
    y = rand() % (gameHeight);
}

