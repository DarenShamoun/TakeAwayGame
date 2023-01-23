//Daren Shamoun
//ID# 5550016094
#include "game.h"

//gets a string entry from the player
std::string get_entry(const std::string prompt)
{
	std::cout << prompt;
	std::string input;
	std::getline(std::cin, input);

	if (input == "\n")
	{
		std::cout << "You did not enter a value, try again. \n";
		get_entry(prompt);
	}

	return input;
}

//gets a uint32_t entry from the player
uint32_t get_value(std::string prompt)
{
	std::cout << prompt;
	uint32_t userValue;
	bool valid = true;

	while (valid)
	{
		std::cin >> userValue;
		if (!std::cin)
		{
			std::cout << "The value you entered is invalid, try again: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		break;
	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return userValue;
}

//creates an empty vector which can have either 
//a defined size from the player or a random one 
std::vector<uint32_t> pileVectorCreator(mesa::option userOptions)
{
	std::vector<uint32_t> pilesVector(userOptions.piles);

	//randomized values for each pile
	if (userOptions.piles == 0)
	{
		std::random_device rand;
		std::mt19937 engine3(rand());
		std::uniform_int_distribution<uint32_t> distr(2, 10);
		uint32_t randomNumberOfPiles = uint32_t(distr(rand));
		pilesVector.resize(randomNumberOfPiles);
	}

	//In the case the player sets the values
	if (userOptions.piles <= 10 && userOptions.piles >= 1)
	{
		pilesVector.resize(userOptions.piles);
	}

	userOptions.piles = uint32_t (pilesVector.size());
	return pilesVector;
}

//populates the vector with random values or
//the values that the player set
std::vector<uint32_t> setNumberOfStones(std::vector<uint32_t> pileVector, mesa::option userOptions)
{
	std::vector<uint32_t> pilesVector = pileVector;

	//In the case the player sets the values
	if (userOptions.stones >= 1)
	{
		for (auto i = 0; i < pilesVector.size(); i++)
		{
			pilesVector[i] = userOptions.stones;
		}
	}

	//randomized values for each pile
	if (userOptions.stones == 0)
	{
		std::random_device rand;
		std::mt19937 engine3(rand());
		std::uniform_int_distribution<uint32_t> distr(2, 20);

		for (auto i = 0; i < pilesVector.size(); i++)
		{
			pilesVector[i] = uint32_t(distr(rand));
		}
	}

	return pilesVector;
}