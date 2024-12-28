//  TOURENNE    FERRY
//  Vincent     Antonny

#pragma once
#include <string>
#include <vector>
#include "token.h"
#include "Player.h"
#include "Renderer.h"

namespace kpt
{
	class GameManager
	{
		std::vector<Player> players;		// Liste des joueurs
		// const Board<int, int> board;		// Plateau de jeu
		Renderer renderer;					// Affichage
		std::vector<flag> flags;			// Liste de Drapeaux

	public:
		GameManager(const std::string& filePath);

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

