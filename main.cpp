#include <iostream>
#include <thread>
#include <chrono>

#include "game/Game.h"
#include "entities/Snake.h"
#include "game/GameMenu.h"
#include "utils/constants.h"
#include "utils/FilePrinter.h"

// void showHelp() {
//     std::cout << "Usage: ./snejks [options]" << std::endl << std::endl;
//     std::cout << "Options:" << std::endl;
//     std::cout << "  --help, -h    Show help message." << std::endl;
//     std::cout << "  --play, -p    Launch the game without menu, with default settings." << std::endl;
// }

int main(const int argc, char *argv[]) {

    turnOnCbreak(); //enable 'raw' mode
    GameMenu game_menu;
    // parse arguments
    for (int i = 0; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--help" || arg == "-h") {
            FilePrinter::printFile("res/help_text.txt");
            return 0;
        }
        if (arg == "--play" || arg == "-p") {
            game_menu.startGame();
            return 0;
        }
    }

    // launch the game normally
    game_menu.gameLoop();
    turnOffCbreak();
    return 0;
}
