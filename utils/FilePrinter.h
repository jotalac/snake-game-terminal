//
// Created by jotalac on 10/19/25.
//

#ifndef SNAKE_TEST_PRINTER_H
#define SNAKE_TEST_PRINTER_H
#include <string>


class FilePrinter {
public:
    static void printFile(const std::string& filePath);
    static void clearField();
};


#endif //SNAKE_TEST_PRINTER_H