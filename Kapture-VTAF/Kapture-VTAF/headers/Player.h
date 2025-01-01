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

		Player(): f_flag(flag("J1", {0, 0}))
		{
		}

		Player(const Player& other): name(other.name), f_flag(other.f_flag)
		{
			if (this == &other) return;
			for (token* t : other.tokens){
				tokens.push_back(t);
			}
			for (std::pair<int, int> pair : other.visitedCells){
				visitedCells.push_back(pair);
			}

		}

		Player& operator=(const Player& other)
		{
			if (this == &other) return *this;
			for (token* t : other.tokens){
				tokens.push_back(t);
			}
			for (std::pair<int, int> pair : other.visitedCells){
				visitedCells.push_back(pair);
			}
			this->f_flag = other.f_flag;

			return *this;
		}
		bool operator==(const Player& other) const
		{
			return this->name == other.name;
		}

		~Player()
		{
			for (token* t : tokens)
				delete t;
		}

		const std::vector<token*>& getTokens() const { return tokens; }
		const flag& getFlag() const { return f_flag; }
	};
}

