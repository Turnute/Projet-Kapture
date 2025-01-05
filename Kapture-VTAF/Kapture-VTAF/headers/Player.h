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
		// Constructeurs & Destructeur
		Player() : f_flag(flag("P1", { 0, 0 })) {}
		Player(
			const std::string& name, 
			const std::vector<std::pair<enum_token, std::pair<int, int>>>& tokens,
			const std::pair<int, int>& f_flag
		);
		Player(const Player& other);
		~Player();

		// Surcharge d'opérateurs
		Player& operator=(const Player& other);
		bool operator==(const Player& other) const;

		// Getters & Setters
		std::string const getName() const { return name; }
		const std::vector<token*>& getTokens() const { return tokens; }
		flag& getFlag() { return f_flag; }
		flag const getFlag() const { return f_flag; }

		// Méthodes
		void addVisitedCell(const std::pair<int, int>& pos);
		bool hasVisitedCell(int i, int j) const;
	};
}

