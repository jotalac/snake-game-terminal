//
// Created by jotalac on 10/25/25.
//
#ifndef SNEJKS_CONSTANTS_H
#define SNEJKS_CONSTANTS_H
#include <map>
#include <string>

const std::string black = "\e[0;30m";
const std::string red = "\e[0;31m";
const std::string green = "\e[0;32m";
const std::string yellow = "\e[0;33m";
const std::string blue = "\e[0;34m";
const std::string purple = "\e[0;35m";
const std::string cyan = "\e[0;36m";
const std::string white = "\e[0;37m";
const std::string titleStyle = "\e[4;32m";
const std::string resetStyle = "\e[0m";

std::map<int, std::string> difficultiesMap = {
    {0, "Noob"},
    {1, "Easy"},
    {2, "Normal"},
    {3, "Hard"},
    {4, "Veryl hard"},
    {5, "God mode"},
};


#endif //SNEJKS_CONSTANTS_H