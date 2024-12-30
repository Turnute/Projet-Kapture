//  TOURENNE    FERRY
//  Vincent     Antony

#pragma once
#include <vector>
#include <utility>
#include <string>
#include "token.h"
#include "flag.h"

namespace kpt
{
	class Player
	{
		const std::string name;							// Nom du joueur (J1 ou J2)
		std::vector<token*> tokens;						// Liste des pions
		std::vector<std::pair<int, int>> visitedCells;	// Positions visitées (brouillard de guerre)
		flag f_flag;									// Drapeau
	public:
		Player(const std::string& name, const std::vector<std::pair<enum_token, std::pair<int, int>>>& tokens,
		       const std::pair<int, int>& f_flag);

		Player(const Player&) = delete;
		Player& operator=(const Player& other) = delete;
		Player() = delete;

		~Player()
		{
			for (token* t : tokens)
				delete t;
		}
	};
}

