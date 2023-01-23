//Daren Shamoun
#ifndef GAME_H
#define GAME_H
#include "options.h"
#include "computer_player.h"
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

void displayNames(mesa::option playerOptions);

void displayGameState(std::vector<uint32_t> inputVector);

game::gameState checkVictory(std::vector<uint32_t> pileVector, game::gameState inputState, mesa::option playerOptions);

void player1Turn(game::gameState& inputState, std::vector<uint32_t>& pileVector, mesa::option& playerOptions);

void player2Turn(game::gameState& currentState, std::vector<uint32_t>& pileVector, mesa::option& playerOptions);

void aiTurn(game::gameState& currentState, std::vector<uint32_t>& pileVector, mesa::option& playerOptions);

#endif // !GAME_H