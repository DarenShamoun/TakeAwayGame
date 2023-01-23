//Daren Shamoun
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
	const bool valid = true;

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
		const std::mt19937 engine3(rand());
		std::uniform_int_distribution<uint32_t> distr(2, 10);
		const uint32_t randomNumberOfPiles = uint32_t(distr(rand));
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
		const std::mt19937 engine3(rand());
		std::uniform_int_distribution<uint32_t> distr(2, 20);

		for (auto i = 0; i < pilesVector.size(); i++)
		{
			pilesVector[i] = uint32_t(distr(rand));
		}
	}

	return pilesVector;
}


//player #1's turn logic
void player1Turn(game::gameState& currentState, std::vector<uint32_t>& pileVector, mesa::option& playerOptions)
{
	currentState = evaluate(pileVector, currentState);
	std::cout << '\n' << playerOptions.player1Name << "'s turn,";
	displayGameState(pileVector);

	//Player 1 selects the pile they want to take from
	currentState.targetPile = get_value("\nWhich pile would you like to take from?: ");
	while (currentState.targetPile <= 0 || currentState.targetPile > currentState.numberOfPiles || pileVector[currentState.targetPile - 1] == 0)
	{
		std::cout << "You must choose a pile displayed above, ";
		std::cout << "Try again:";
		currentState.targetPile = get_value(" ");
	}
	currentState.targetPile--;

	//Player 1 selects the amount of stones they want to take from the pile
	currentState.numberToRemove = get_value("How many stones would you like to take?: ");
	while (currentState.numberToRemove > pileVector[currentState.targetPile] || currentState.numberToRemove < 1)
	{
		std::cout << "Invalid entry! ";
		std::cout << "Try again:";
		currentState.numberToRemove = get_value(" ");
	}
	pileVector[currentState.targetPile] -= currentState.numberToRemove;
	currentState = evaluate(pileVector, currentState);
	currentState = checkVictory(pileVector, currentState, playerOptions);
}

//player #2's turn logic
void player2Turn(game::gameState& currentState, std::vector<uint32_t>& pileVector, mesa::option& playerOptions)
{
	std::cout << '\n' << playerOptions.player2Name << "'s turn,";
	displayGameState(pileVector);

	//Player 2 selects the pile they want to take from
	currentState.targetPile = get_value("\nWhich pile would you like to take from?: ");
	while (currentState.targetPile <= 0 || currentState.targetPile > currentState.numberOfPiles || pileVector[currentState.targetPile - 1] == 0)
	{
		std::cout << "You must choose a pile displayed above, ";
		std::cout << "Try again:";
		currentState.targetPile = get_value(" ");
	}
	currentState.targetPile--;

	//Player 2 selects the amount of stones they want to take from the pile
	currentState.numberToRemove = get_value("How many stones would you like to take?: ");
	while (currentState.numberToRemove > pileVector[currentState.targetPile] || currentState.numberToRemove < 1)
	{
		std::cout << "Invalid entry! ";
		std::cout << "Try again:";
		currentState.numberToRemove = get_value(" ");
	}
	pileVector[currentState.targetPile] -= currentState.numberToRemove;

	currentState = evaluate(pileVector, currentState);
	currentState = checkVictory(pileVector, currentState, playerOptions);
}

//AI's turn logic
void aiTurn(game::gameState& currentState, std::vector<uint32_t>& pileVector, mesa::option& playerOptions)
{
	//AI's turn begins here
	std::cout << '\n' << playerOptions.player2Name << "'s turn,";
	currentState = evaluate(pileVector, currentState);

	if (currentState.takeOne)
	{
		pileVector = take_one(pileVector, currentState.targetPile);

		std::cout << '\n' << playerOptions.player2Name << " removed "
			<< currentState.numberToRemove << " stone from pile "
			<< currentState.targetPile + 1 << '\n';
	}

	if (!currentState.takeOne)
	{
		pileVector = take_some(pileVector, currentState);
		std::cout << '\n' << playerOptions.player2Name << " removed "
			<< currentState.numberToRemove << " stones from pile "
			<< currentState.targetPile + 1 << '\n';
		currentState.takeOne = true;
	}
}

//function to display the current player names
void displayNames(mesa::option playerOptions)
{
	if (playerOptions.has_ai)
	{
		std::cout << "\nPlayer 1: " + playerOptions.player1Name << '\n';
		std::cout << "AI: " + playerOptions.player2Name << "\n\n";
	}
	if (!playerOptions.has_ai)
	{
		std::cout << "\nPlayer 1: " + playerOptions.player1Name << '\n';
		std::cout << "Player 2: " + playerOptions.player2Name << "\n\n";
	}
}

//function to display the current game state
void displayGameState(std::vector<uint32_t> inputVector)
{
	std::vector<uint32_t> gameVector = inputVector;
	std::cout << '\n' << std::string(35, '-');
	for (auto i = 0; i < gameVector.size(); i++)
	{
		if (gameVector[i] != 0)
		{
			std::cout << "\nPile " << std::setw(2) << (i + 1) << " [" << std::setw(2)
				<< gameVector[i] << "]: " << std::string(gameVector[i], '*');
		}
	}
	std::cout << '\n' << std::string(35, '-');
}

//function to check if someone has won and handle responses afterwards
game::gameState checkVictory(std::vector<uint32_t> pileVector, game::gameState inputState, mesa::option playerOptions)
{
	game::gameState currentState = inputState;
	currentState = evaluate(pileVector, currentState);

	if (currentState.player1Turn && currentState.totalStones < 1)
	{
		currentState.win = true;
		std::cout << '\n' << playerOptions.player1Name << " has won!\n";

		char userAnswer = NULL;
		const bool valid = true;
		while (valid)
		{
			std::cout << "Would you like to play again? [Y/N] " << std::endl;
			std::cin >> userAnswer;
			userAnswer = char(tolower(userAnswer));
			if (userAnswer == 'y' || userAnswer == 'n') { break; }

			std::cout << "You may only type 'Y' or 'N'.\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	if (!currentState.player1Turn && currentState.totalStones < 1)
	{
		currentState.win = true;
		std::cout << '\n' << playerOptions.player2Name << " has won!\n";

		char userAnswer = NULL;
		const bool valid = true;
		while (valid)
		{
			std::cout << "Would you like to play again? [Y/N] " << std::endl;
			std::cin >> userAnswer;
			userAnswer = char(tolower(userAnswer));
			if (userAnswer == 'y') { break; }

			if (userAnswer == 'n')
			{
				currentState.again = false;
				break;
			}

			std::cout << "You may only type 'Y' or 'N'.\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return currentState;
}