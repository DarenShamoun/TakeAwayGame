//Daren Shamoun
//ID# 5550016094
#ifndef CISC187_MESA_COMPUTER_PLAYER_H
#define CISC187_MESA_COMPUTER_PLAYER_H
#include <cstdint>
#include <vector>

namespace game
{
	struct gameState
	{
		uint32_t numberOfPiles = 0;
		uint32_t totalStones = 0;
		uint32_t largestPile = 0;
		uint32_t stonesInLargest = 0;
		uint32_t nimSum = 0;
		uint32_t targetPile = 0;
		uint32_t numberToRemove = 0;
		bool takeOne = true;
		bool win = false;
		bool again = true;
		bool player1Turn = true;
	};
}

uint32_t nimSumCalculate(std::vector<uint32_t> pilesVector);

game::gameState findPileValues(std::vector<uint32_t> pilesVector, game::gameState inputState);

game::gameState evaluate(std::vector<uint32_t> pilesVector, game::gameState inputState);

std::vector<uint32_t> take_one(std::vector<uint32_t> pilesVector, uint32_t inputState);

std::vector<uint32_t> take_some(std::vector<uint32_t> pilesVector, game::gameState inputState);

#endif // !CISC187_MESA_COMPUTER_PLAYER_H