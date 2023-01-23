//Daren Shamoun
#include "options.h"
#include "game.h"
#include "computer_player.h"

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

		//Keeps the current game going until there are no stones left
		while (currentState.totalStones >= 1)
		{
		//Activates when the player is facing the AI
			if (playerOptions.has_ai)
			{
				//Begins player's turn
				player1Turn(currentState, pileVector, playerOptions);
				if (currentState.win) { break; }
				currentState.player1Turn = false;

				//Begins AI's turn
				aiTurn(currentState, pileVector, playerOptions);
			}

			//Reprints the game board
			currentState = evaluate(pileVector, currentState);
			currentState = checkVictory(pileVector, currentState, playerOptions);
			if (currentState.win) { break; }

			currentState.player1Turn = true;

			
		//Activates only when there are two players
			if (!playerOptions.has_ai)
			{
				//Player 1's turn begins here
				player1Turn(currentState, pileVector, playerOptions);
				if (currentState.win) { break; }
				currentState.player1Turn = false;

				//Player 2's turn begins here
				player2Turn(currentState, pileVector, playerOptions);
				if (currentState.win) { break; }
				currentState.player1Turn = true;
			}
			currentState = checkVictory(pileVector, currentState, playerOptions);
			if (currentState.win) { break; }
		}
	}
	return 0;
}