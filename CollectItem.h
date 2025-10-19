//
// Created by jotalac on 10/19/25.
//

#ifndef SNAKE_TEST_COLLECTITEM_H
#define SNAKE_TEST_COLLECTITEM_H


class CollectItem {
private:
    int x = 0;
    int y = 0;
public:
    int getX() const;
    int getY() const;

    void respawnItem(int gameWidth, int gameHeight);

};


#endif //SNAKE_TEST_COLLECTITEM_H