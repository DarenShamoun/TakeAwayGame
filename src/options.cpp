//Daren Shamoun
//ID# 5550016094
#include "options.h"
#include "game.h"

//displays the possible command line arguements
std::string usage(const char* argv)
{
	std::string input(argv);
	std::string usage = "Usage: " + input + " [-h] [-c] [-p # piles] [-s # stones]\n";
	
	return usage;
}

//displays the full help text along with the file name
std::string help(const char* argv)
{
	std::string helpText = usage(argv) + "\n-h: Displays the help text." 
		+ "\n-c: Enables the computer player as player 2"
		+ "\n-p: Set a value for piles in the range 2-10" 
		+ "\n-s: Set a value for stones in the range 2-20 \n";

	return helpText;
}

//parses the command line arguements and returns the users desired settings
mesa::option get_options (int argc, const char** argv)
{
	mesa::option userOptions;

	//loops through each arguement
	for (auto i = 0; i < argc; i++)
	{
		//if found displays help text
		if (std::strcmp(argv[i], "-h") == 0)
		{
			userOptions.valid = false;
			std:: cout << help(argv[i]) << '\n';
			break;
		}

		//if found enables the computer player
		if (std::strcmp(argv[i], "-c") == 0)
		{
			userOptions.has_ai = true;
		}

		//if found sets the number of piles
		if (std::strcmp(argv[i], "-p") == 0)
		{
			if (i + 1 >= argc)
			{
				userOptions.valid = false;
				std::cout << "Invalid entry! (-p)\n";
				std::cout << "You did not enter a value!\n";
				break;
			}

			if (strtol(argv[i + 1], nullptr, 0) < 2 || strtol(argv[i + 1], nullptr, 0) > 10)
			{
				userOptions.valid = false;
				std::cout << "Invalid entry! (-p)\n";
				std::cout << "You can only enter a value between 2 and 10!\n";
				break;
			}

			userOptions.piles = uint32_t(strtol(argv[i + 1], nullptr, 0));
		}

		//if found sets the number of stones per pile
		if (std::strcmp(argv[i], "-s") == 0)
		{
			if (i + 1 >= argc)
			{
				userOptions.valid = false;
				std::cout << "Invalid entry! (-s)\n";
				std::cout << "You did not enter a value!\n";
				break;
			}

			if (strtol(argv[i + 1], nullptr, 0) < 2 || strtol(argv[i + 1], nullptr, 0) > 10)
			{
				userOptions.valid = false;
				std::cout << "Invalid entry! (-s)\n";
				std::cout << "You can only enter a value between 2 and 20!\n";
				break;
			}

			userOptions.stones = uint32_t(strtol(argv[i + 1], nullptr, 0));
		}
	}

	//asks for only the humans name (when vs AI)
	if (userOptions.has_ai && userOptions.valid)
	{
		userOptions.player1Name = get_entry("\nHuman player's name: ");
	}

	//asks for both players names
	if (!userOptions.has_ai && userOptions.valid)
	{
		userOptions.player1Name = get_entry("\nPlayer 1's name: ");
		userOptions.player2Name = get_entry("Player 2's name: ");
	}

	return userOptions;
}