//
// Created by jotalac on 22.10.25.
//

#include "GameMenu.h"

#include <iomanip>
#include <iostream>

#include "../utils/constants.h"
#include "../utils/FilePrinter.h"

GameMenu::GameMenu() {
}

void GameMenu::gameLoop() {
    bool running = true;
    while (running) {
        running = showMenu();
    }
}

void GameMenu::startGame() {
    const Snake snake{1, 1, "▓", "@", 2};
    // game = std::make_unique<Game>(30, 30, snake, 10);
    Game game{30, 30, snake, 10};

    game.startGame();

    while (game.isGameRunning()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}


bool GameMenu::showMenu() {
    FilePrinter::clearField();
    FilePrinter::printFile("../resources/menu_title.txt", true);
    const auto startSpace = std::string(20, ' ');
    std::cout << startSpace << titleStyle << "Select action" << std::endl << std::endl;
    std::cout << white << startSpace << "1) start game" << std::endl;
    std::cout << white << startSpace << "2) settings" << std::endl;
    std::cout << red << startSpace << "3) exit" << resetStyle << std::endl;
    // std::cout << "Select action: \n1)start game \n2)settings \n3)exit \n";

    std::string action;
    std::cin >> action;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer

    if (action == "1") {
        startGame();
        return true;
    }
    if (action == "2") {
        showSettings();
        return true;
    }
    if (action == "3") {
        return false;
    }

    return true; // Any other input, stay in menu
}

void GameMenu::showSettings() {
    FilePrinter::clearField();
    FilePrinter::printFile("../resources/settings_title.txt");

    const auto startSpace = std::string(10, ' ');
    std::cout << startSpace << purple << "Press the number to change the value:" << std::endl << std::endl;
    std::cout << white << startSpace << "1) game width: " << game_width() << std::endl;
    std::cout << white << startSpace << "2) game height: " << game_height() << std::endl;
    std::cout << white << startSpace << "2) difficultly: " << game_difficulty() << std::endl;
    std::cout << red << startSpace << "3) spawn obstacles: " << game_walls() << resetStyle << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}



