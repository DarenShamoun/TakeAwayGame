//Daren Shamoun
#ifndef OPTIONS_H
#define OPTIONS_H
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <string>

namespace mesa
{
	struct option
	{
		bool valid = true;
		bool has_ai = true;
		uint32_t piles = 0;
		uint32_t stones = 0;
		std::string player1Name = "Player1";
		std::string player2Name = "ULTRON";
	};
}

mesa::option get_options(int argc, const char** argv);

std::string usage(const char* argv);

std::string help(const char* argv);

#endif // !OPTIONS_H