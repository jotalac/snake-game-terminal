//
// Created by jotalac on 22.10.25.
//

#include "GameMenu.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

#include "../utils/constants.h"
#include "../utils/FilePrinter.h"

void GameMenu::gameLoop() {
    srand(std::time(0));

    bool running = true;
    while (running) {
        running = showMenu();
    }
}

void GameMenu::startGame() const {
    const Snake snake{1, 1, "▓", "@", 2};
    Game game{snake, gameWalls, gameWidth, gameHeight, gameDifficulty};

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
    std::cout << white << startSpace << "3) controls" << std::endl << std::endl;
    std::cout << red << startSpace << "4) exit" << resetStyle << std::endl;

    while (true) {
        const char action = getchar();

        // std::string action;
        // std::cin >> action;
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer

        if (action == '1') {
            startGame();
            return true;
        }
        if (action == '2') {
            showSettings();
            return true;
        }
        if (action == '3') {
            showControls();
            return true;
        }
        if (action == '4') {
            return false;
        }
    }
}

void GameMenu::showSettings() {
    while (true) {
        FilePrinter::clearField();
        FilePrinter::printFile("../resources/settings_title.txt");

        const auto startSpace = std::string(4, ' ');
        std::cout << std::boolalpha;
        std::cout << startSpace << green << "Press the number to change the value:" << std::endl << std::endl;
        std::cout << white << startSpace << "1) game width: " << green << gameWidth << std::endl;
        std::cout << white << startSpace << "2) game height: " << green << gameHeight << std::endl;
        std::cout << white << startSpace << "3) difficultly: " << green << difficultiesMap[gameDifficulty] << std::endl;
        std::cout << white << startSpace << "4) spawn walls: " << green << gameWalls << std::endl << std::endl;
        std::cout << red << startSpace << "5) exit settings" << resetStyle << std::endl;

        const char action = getchar();

        if (action == '1') {
            changeGameSize(gameWidth, "width");
        } else if (action == '2') {
            changeGameSize(gameHeight, "height");
        } else if (action == '3') {
            gameDifficulty = ++gameDifficulty % difficultiesMap.size();
        } else if (action == '4') {
          gameWalls = !gameWalls;
        } else if (action == '5') {
            break;
        }

    }
}

void GameMenu::showControls() {
    while (true) {
        FilePrinter::clearField();
        FilePrinter::printFile("../resources/controls_table.txt");
        std::cout << "    Press any key to exit..." << std::endl;
        getchar();
        break;
    }
}


void GameMenu::changeGameSize(int &side, const std::string &sideName) {
    turnOffCbreak(); // disable raw mode (user can see input)
    while (true) {
        FilePrinter::clearField();
        FilePrinter::printFile("../resources/settings_title.txt");
        std::cout << "Enter " << sideName << ": ";

        std::string action;
        std::cin >> action;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer

        try {
            const int actionNum = std::stoi(action);

            if (actionNum < 3) side = 3;
            else if (actionNum > 100) side = 100;
            else side = actionNum;
            break;
        } catch (const std::invalid_argument e) {
        } catch (const std::out_of_range& e) {
            side = 100;
            break;
        }
    }
    turnOnCbreak();

}




