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
		int currentPlayerindex;			// Trace du joueur actif

	public:
		GameManager(const std::string& filePath);

		// Déroulement d'un tour
		void moveToken(const std::pair<int, int>& token, const std::pair<int, int>& destination);
		void checkSurroundings(std::pair<int, int> position);

		// Affrontement entre tokens
		void battle(token& t1, token& t2);
		void resetToken(token& t_token);

		// Check si la partie est finie
		bool const isOver();

		// Boucle de jeu
		std::pair<int, int> askCoordinates(const std::string& message);
		void playerTurn(const Player& player);
		void gameLoop();

		// Affichage
		void const display() const { renderer.render(currentPlayerindex); }
	};
}

