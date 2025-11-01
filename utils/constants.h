//
// Created by jotalac on 10/25/25.
//
#ifndef SNEJKS_CONSTANTS_H
#define SNEJKS_CONSTANTS_H
#include <map>
#include <string>

constexpr std::string black = "\e[0;30m";
constexpr std::string red = "\e[0;31m";
constexpr std::string green = "\e[0;32m";
constexpr std::string yellow = "\e[0;33m";
constexpr std::string blue = "\e[0;34m";
constexpr std::string purple = "\e[0;35m";
constexpr std::string cyan = "\e[0;36m";
constexpr std::string white = "\e[0;37m";
constexpr std::string titleStyle = "\e[4;32m";
constexpr std::string resetStyle = "\e[0m";

inline std::map<int, std::string> difficultiesMap = {
    {0, "Noob"},
    {1, "Easy"},
    {2, "Normal"},
    {3, "Hard"},
    {4, "Veryl hard"},
    {5, "God mode"},
};

inline void turnOnCbreak() {system("stty cbreak -echo");}
inline void turnOffCbreak() {system("stty -cbreak echo");}


#endif //SNEJKS_CONSTANTS_H