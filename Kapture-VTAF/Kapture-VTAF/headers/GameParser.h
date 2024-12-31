//  TOURENNE    FERRY
//  Vincent     Antony

#pragma once
#include <vector>
#include <string>
#include "cell.h"
#include "token.h"

namespace kpt
{
	class GameParser
	{
		std::vector<enum_cell> cells;
		std::vector<std::string> player_names;
		std::vector<std::vector<std::pair<enum_token, std::pair<int, int>>>> player_tokens;
		std::vector<std::pair<int, int>> player_flags;

	public:
		GameParser(const std::string& filePath);

		// Getters
		std::vector<enum_cell> const getCells();
		std::string const getPlayerName(const int& i);
		std::vector<std::pair<enum_token, std::pair<int, int>>> const getPlayerTokens(const int& i);
		std::pair<int, int> const getPlayerFlag(const int& i);

		// Parsing d'un fichier
		enum_cell const parseCell(const std::string& str);
		enum_token const parseToken(const std::string& str);
		std::pair<int, int> const parsePosition(const std::string& str);
	};
}

