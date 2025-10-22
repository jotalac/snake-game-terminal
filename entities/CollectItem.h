//
// Created by jotalac on 10/19/25.
//

#ifndef SNAKE_TEST_COLLECTITEM_H
#define SNAKE_TEST_COLLECTITEM_H
#include "Item.h"


class CollectItem : public Item {
public:
    CollectItem(const std::string& sign);
    void moveRand(int width, int height);
};


#endif //SNAKE_TEST_COLLECTITEM_H