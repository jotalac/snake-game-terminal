//
// Created by jotalac on 22.10.25.
//

#include "GameMenu.h"

#include <iostream>

#include "../utils/FilePrinter.h"

GameMenu::GameMenu() {
    const Snake snake{1, 1, "▓", "@", 2};
    game = std::make_unique<Game>(30, 30, snake, 10);
}

void GameMenu::gameStartup() {
    while (true) {
        if (!showMenu()) break;
    }
}



bool GameMenu::showMenu() {
    FilePrinter::clearField();
    FilePrinter::printFile("../resources/menu_title.txt");
    std::cout << "Select action: \n1)start game \n2)settings \n3)exit \n";
    int action;
    std::cin >> action;

    switch (action) {
        case 1:
            game->startGame();
            while (game->isGameRunning()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
            }
            return true;
        case 3:
            return false;
        default:
            return true;

    }
}


