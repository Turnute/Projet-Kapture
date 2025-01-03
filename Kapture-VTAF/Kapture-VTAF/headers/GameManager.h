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
		int currentPlayerindex;

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
		std::pair<int, int> askCoordinates(const std::string& message);
		void gameLoop();

		void display() const { renderer.render(currentPlayerindex); }
	};
}

