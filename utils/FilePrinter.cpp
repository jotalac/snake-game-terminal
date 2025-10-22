//
// Created by jotalac on 10/19/25.
//
#include "FilePrinter.h"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>

void FilePrinter::printFile(const std::string& filePath) {
    std::ifstream file(filePath);

    //check if file was opened
    if (!file.is_open()) {
        std::cerr << "Cannot open file for print" << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::cout << line << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(20)); //sleep for while
    }


    file.close();
}
