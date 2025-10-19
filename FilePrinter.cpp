//
// Created by jotalac on 10/19/25.
//
#include "FilePrinter.h"

#include <fstream>
#include <iomanip>
#include <iostream>

void FilePrinter::printFile(const std::string& filePath, int height) {
    std::ifstream file(filePath);

    //check if file was opened
    if (!file.is_open()) {
        std::cerr << "Cannot open file for print" << std::endl;
        return;
    }

    std::string line;
    int lineN = 0;

    while (std::getline(file, line)) {
        std::cout << line << std::endl;
        lineN++;
    }

    if (lineN < height) {
        std::cout << std::setfill('\n') << std::setw(height - lineN) << "" << std::endl;
    }

    file.close();
}
