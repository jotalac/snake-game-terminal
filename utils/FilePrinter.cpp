//
// Created by jotalac on 10/19/25.
//
#include "FilePrinter.h"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>

void FilePrinter::clearField() {
    std::cout << "\033[2J\033[H";
}

void FilePrinter::printFile(const std::string& filePath, bool shouldAnimate) {
    std::ifstream file(filePath);

    //check if file was opened
    if (!file.is_open()) {
        std::cerr << "Cannot open file for print" << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::cout << line << std::endl;

        if (shouldAnimate) std::this_thread::sleep_for(std::chrono::milliseconds(50)); //sleep for while
    }
    file.close();
}
