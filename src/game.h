//Daren Shamoun
//ID# 5550016094
#ifndef CISC187_MESA_GAME_H
#define CISC187_MESA_GAME_H
#include "options.h"
#include <string>
#include <cctype>
#include <vector>
#include <iostream>
#include <random>
#include <ctime>

std::string get_entry(const std::string prompt);

uint32_t get_value(const std::string prompt);

std::vector<uint32_t> pileVectorCreator(mesa::option userOptions);

std::vector<uint32_t> setNumberOfStones(std::vector<uint32_t>, mesa::option userOptions);

#endif // !CISC187_MESA_GAME_H