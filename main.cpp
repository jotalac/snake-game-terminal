#include <chrono>
#include "game/GameMenu.h"
#include "utils/constants.h"
#include "utils/FilePrinter.h"

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
