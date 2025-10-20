//
// Created by jotalac on 10/20/25.
//
#include "Item.h"

#include <cstdlib>
#include <ctime>

Item::Item(const std::string &sign): sign(sign) {}


int Item::getX() const {
    return x;
}

int Item::getY() const {
    return y;
}

std::string Item::getSign() const {
    return sign;
}


void Item::respawnItem(const int gameWidth, const int gameHeight) {
    // srand(std::time(0));

    x = rand() % (gameWidth);
    y = rand() % (gameHeight);
}

