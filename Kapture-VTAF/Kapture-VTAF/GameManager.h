//  TOURENNE    FERRY
//  Vincent     Antony

#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Player.h"
#include "Board.h"
#include "Renderer.h"

namespace kpt
{
	class GameManager
	{
		std::map<int, Player> players;		// Liste des joueurs
		Board board;						// Plateau de jeu
		Renderer renderer;					// Affichage

	public:
		GameManager(const std::string& filePath);

		// Parsing d'un fichier
		enum_cell const parseCell(const std::string& str);
		std::pair<int, int> const parsePosition(const std::string& str);

		// Affrontement entre tokens
		void battle(token& t1, token& t2);
		void resetToken(token& t_token);

		// Déroulement d'un tour
		void moveToken(const Player& owner, const std::pair<int, int>& token, const std::pair<int, int>& destination);
		void checkSurroundings(const token& t_token);
		void playerTurn(const Player& player);

		// Check si la partie est finie
		bool const isOver();

		void gameLoop();
	};
}

