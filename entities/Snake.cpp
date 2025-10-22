#include "Snake.h"

#include <iostream>
#include <string>
#include <utility>

Snake::Snake(const int xPos, const int yPos, const std::string &headSign, const std::string &bodySign, const int length)
    : headX(xPos), headY(yPos), headSign(headSign + headSign), bodySign(bodySign + bodySign), length(length) {
    //init the snake tail coords
    for (int i = 0; i < length - 1; i++) {
        tailCoords.push_back({headX - i - 1, headY});
    }
    std::cout << tailCoords.size();
}

void Snake::moveTo(const int xTo, const int yTo) {
    headX = xTo;
    headY = yTo;
}

int Snake::getHeadX() const {
    return headX;
}

int Snake::getHeadY() const {
    return headY;
}

std::vector<std::pair<int, int> > Snake::getTailCoords() const{
    return tailCoords;
}



int Snake::getXVec() const {
    return x_vec;
}

int Snake::getYVec() const {
    return y_vec;
}

void Snake::setXVec(const int new_vec) {
    x_vec = new_vec;
}

void Snake::setYVec(const int new_vec) {
    y_vec = new_vec;
}

std::string Snake::getHeadSign() const {
    return headSign;
}

std::string Snake::getBodySign() const {
    return bodySign;
}


void Snake::updateHead() {
    moveTo(headX + getXVec(), headY + getYVec());
}

void Snake::setDirection(std::string newDir) {
    direction = newDir;
}

std::string Snake::getDirection() {
    return direction;
}




void Snake::updateTail() {
    for (int i = tailCoords.size() - 1; i >= 0; --i) {
        if (i == 0) {
            tailCoords[0] = {headX, headY};
            continue;
        }
        tailCoords[i] = tailCoords[i - 1];
    }
}

void Snake::incrementSize() {
    length++;
    // std::pair<int, int> last_part =
    tailCoords.push_back({tailCoords[tailCoords.size() - 1].first, tailCoords[tailCoords.size() - 1].second});
}









#include "Snake.h"
