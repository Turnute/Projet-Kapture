//  TOURENNE    FERRY
//  Vincent     Antony

#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Player.h"
#include "Board.h"
#include "Renderer.h"
#include "GameParser.h"

namespace kpt
{
	class GameManager
	{
		std::vector<Player> players;	// Liste des joueurs
		Board board;					// Plateau de jeu
		Renderer renderer;				// Affichage

	public:
		GameManager(const std::string& filePath);

		// Affrontement entre tokens
		void battle(token& t1, token& t2);
		void resetToken(token& t_token);

		// Déroulement d'un tour
		void moveToken(const std::pair<int, int>& token, const std::pair<int, int>& destination);
		void checkSurroundings(std::pair<int, int> position);
		void playerTurn(const Player& player);

		// Check si la partie est finie
		bool const isOver();

		// Boucle de jeu
		void gameLoop();

		void display() const { renderer.render(); }
	};
}

