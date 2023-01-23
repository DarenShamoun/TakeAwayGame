//Daren Shamoun
//ID# 5550016094
#include "options.h"
#include "game.h"
#include "computer_player.h"

void displayNames(mesa::option playerOptions);
void displayGameState(std::vector<uint32_t> inputVector);
game::gameState checkVictory(std::vector<uint32_t> pileVector, game::gameState inputState, mesa::option playerOptions);

int main(int argc, const char* argv[])
{
	//Initializes the first gameState
	game::gameState currentState = { 0,0,0,0,0,0,0, true, false, true, true };

	//initial game loop
	while (currentState.again)
	{
		//checks to see if the player started a new game or if they wanted to exit the game
		if (currentState.win && !currentState.again) {break;}

		//sets the state to initial values
		currentState = { 0,0,0,0,0,0,0, true, false, true, true };
		mesa::option playerOptions = get_options(argc, argv);
		if (!playerOptions.valid) { break; }
		displayNames(playerOptions);

		//creates the game vector which stores the current game data
		std::vector<uint32_t> pileVector = pileVectorCreator(playerOptions);
		pileVector = setNumberOfStones(pileVector, playerOptions);
		currentState = evaluate(pileVector, currentState);

		//Kepps the current game going until there are no stones left
		while (currentState.totalStones >= 1)
		{
//Activates when the player is facing the AI
			if (playerOptions.has_ai)
			{
	//Begins player's turn
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
				if (currentState.win) { break; }

				currentState.player1Turn = false;
				std::cout << '\n' << playerOptions.player2Name << "'s turn,";
	//Ends player's turn

				//Reprints the game board
				displayGameState(pileVector);

	//The turn of the AI begins and it decides based on evaluate function
				
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
	//Ends Ai's turn
			}

			//Reprints the game board
			currentState = evaluate(pileVector, currentState);
			currentState = checkVictory(pileVector, currentState, playerOptions);
			if (currentState.win) { break; }

			currentState.player1Turn = true;

//Activates when the player is not using AI
			if (!playerOptions.has_ai)
			{
	//Player 1's turn begins here
				currentState = evaluate(pileVector, currentState);
				std::cout << '\n' << playerOptions.player1Name << "'s turn,";
				displayGameState(pileVector);

				//Player 1 selects the pile they want to take from
				currentState.targetPile = get_value("\nWhich pile would you like to take from?: ");
				while (currentState.targetPile <= 0 || currentState.targetPile > currentState.numberOfPiles || pileVector[currentState.targetPile -1] == 0)
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
				if (currentState.win) { break; }

				currentState.player1Turn = false;
	//Ends player 1's turn

				//Reprints the game board
				std::cout << '\n' << playerOptions.player2Name << "'s turn,";
				displayGameState(pileVector);

	//Player 2's turn begins here

				//Player 2 selects the pile they want to take from
				currentState.targetPile = get_value("\nWhich pile would you like to take from?: ");
				while (currentState.targetPile <= 0 || currentState.targetPile > currentState.numberOfPiles || pileVector[currentState.targetPile -1] == 0)
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
				if (currentState.win) { break; }

				currentState.player1Turn = true;
	//Ends player 2's turn

				//Reprints the board with the updated state
			}

			currentState = checkVictory(pileVector, currentState, playerOptions);
			if (currentState.win) { break; }
		}
	}
	return 0;
}

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

game::gameState checkVictory(std::vector<uint32_t> pileVector, game::gameState inputState, mesa::option playerOptions)
{
	game::gameState currentState = inputState;
	currentState = evaluate(pileVector, currentState);

	if (currentState.player1Turn && currentState.totalStones < 1)
	{
		currentState.win = true;
		std::cout << '\n' << playerOptions.player1Name << " has won!\n";
		
		char userAnswer = NULL;
		bool valid = true;
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
		bool valid = true;
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