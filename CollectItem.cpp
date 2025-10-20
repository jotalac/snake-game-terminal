//
// Created by jotalac on 10/19/25.
//
#include "CollectItem.h"

#include <ctime>
#include <random>


CollectItem::CollectItem(const std::string& sign) : Item(sign) {}

void CollectItem::moveRand(int width, int height) {
    switch (rand() % 4) {
        case 0:
            if (x< width) {
                x++;
            }
            break;
        case 1:
            if (x > 0) {
                x--;
            }
        case 2:
            if (y < height) {
                y++;
            }
        case 3:
            if (y > 0) {
                y--;
            }
            break;
    }
}
