//Daren Shamoun
//ID# 5550016094
#include "computer_player.h"

//calculates the nimsum 
uint32_t nimSumCalculate(std::vector<uint32_t> pilesVector)
{
	uint32_t nimSum = 0;
	for (auto i : pilesVector)
	{
		nimSum ^= i;
	}
	return nimSum;
}

//calculates basic amounts of stones per pile and totals 
game::gameState findPileValues(std::vector<uint32_t> pilesVector, game::gameState inputState)
{
	//takes the passed state and sets all the pile values to 0 
	 game::gameState currentState = { 0,0,0,0,0,0,0, inputState.takeOne, inputState.win, inputState.again, inputState.player1Turn};
	currentState.numberOfPiles = uint32_t(pilesVector.size());
	
	//calculates the totals for the important piles
	for (auto i = 0; i < pilesVector.size(); i++)
	{
		currentState.totalStones += pilesVector[i];

		if (pilesVector[i] > currentState.stonesInLargest)
		{
			currentState.largestPile = i;
			currentState.stonesInLargest = pilesVector[i];
		}
	}
	return currentState;
}

//calculates the best target pile and how many need to be removed
game::gameState calculateTargets(std::vector<uint32_t> pilesVector, game::gameState inputState)
{
	game::gameState currentState = inputState;

	//when the given nimSum is zero the best move for the AI is to take 1
	if (currentState.nimSum == 0)
	{
		currentState.targetPile = currentState.largestPile;
		currentState.numberToRemove = 1;
	}

	//when nimSum is not zero the AI will remove stones from the largest pile
	//until it becomes zero
	if (currentState.nimSum != 0)
	{
		currentState.targetPile = currentState.largestPile;
		currentState.numberToRemove = 0;
		std::vector<uint32_t> tempVect = pilesVector;
		game::gameState tempGameState = currentState;
		tempGameState.numberToRemove = 0;

		//removes stones from a temporary vector and calculates 
		//the nimSum of it without changing the original vector
		while (tempGameState.nimSum != 0)
		{
			uint32_t counter = 0;
			tempGameState.numberToRemove++;
			if (tempVect[tempGameState.targetPile] != 0)
			{
				tempVect[tempGameState.targetPile]--;
			}
			tempGameState.nimSum = nimSumCalculate(tempVect);
		
			if (tempGameState.nimSum != 0 && tempVect[tempGameState.targetPile] == 0)
			{
				tempGameState.targetPile++;
				counter++;
				
				if (tempVect.size() - 1 < tempGameState.targetPile)
				{
					tempGameState.targetPile = 0;
				}
				tempVect = pilesVector;
				tempGameState.numberToRemove = 0;
				tempGameState.nimSum = nimSumCalculate(tempVect);
			}

			if (tempGameState.numberToRemove > 1)
			{
				tempGameState.takeOne = false;
			}

			if (counter > tempGameState.numberOfPiles)
			{
				tempGameState.takeOne = true;
				tempGameState.targetPile = tempGameState.largestPile;
				tempGameState.numberToRemove = 1;
				break;
			}
		}

		currentState.numberToRemove = tempGameState.numberToRemove;
		currentState.targetPile = tempGameState.targetPile;
		currentState.takeOne = tempGameState.takeOne;
	}
	return currentState;
}

//Evaluates the current state of the board by
//combining the previous 3 functions 
game::gameState evaluate(const std::vector<uint32_t> pilesVector, game::gameState inputState)
{
	game::gameState currentState = inputState;
	currentState = findPileValues(pilesVector, currentState);
	currentState.nimSum = nimSumCalculate(pilesVector);
	currentState = calculateTargets(pilesVector, currentState);
	
	return currentState;
}

//removes a single stone from the largest pile
std::vector<uint32_t> take_one(std::vector<uint32_t> inputVector, uint32_t targetPile)
{
	std::vector<uint32_t> pilesVector = inputVector;
	pilesVector[targetPile] -= 1;
	return pilesVector;
}

//removes multiple stones from the target pile
std::vector<uint32_t> take_some(std::vector<uint32_t> inputVector, game::gameState inputState)
{
	std::vector<uint32_t> pilesVector = inputVector;
	game::gameState currentState = inputState;
	pilesVector[currentState.targetPile] -= currentState.numberToRemove;
	return pilesVector;
}