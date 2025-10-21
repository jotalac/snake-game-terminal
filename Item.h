//
// Created by jotalac on 10/20/25.
//

#ifndef SNAKE_TEST_ITEM_H
#define SNAKE_TEST_ITEM_H
#include <string>


class Item {
protected:
    int x = 0;
    int y = 0;
    std::string sign;
public:
    Item(const std::string &sign);
    int getX() const;
    int getY() const;
    void setX(int newX);
    void setY(int newY);
    std::string getSign() const;

    void respawnItem(int gameWidth, int gameHeight);
};


#endif //SNAKE_TEST_ITEM_H