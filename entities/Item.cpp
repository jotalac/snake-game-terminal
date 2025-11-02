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

void Item::setX(const int newX) {
    x = newX;
}

void Item::setY(const int newY) {
    y = newY;
}



std::string Item::getSign() const {
    return sign;
}


void Item::respawnItem(const int gameWidth, const int gameHeight) {
    x = rand() % (gameWidth);
    y = rand() % (gameHeight);
}

