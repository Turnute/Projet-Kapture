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
		const std::vector<Player> players;
		// const Board<int, int> board;
		Renderer renderer;
	public:
		GameManager(const std::string& filePath);

		// Déroulement d'un tour
		void moveToken(const Player& owner, const std::pair<int, int>& token, const std::pair<int, int>& destination);
		void checkSurroundings(const token& t_token);
		void playerTurn(const Player& player);

		// Check si la partie est finie
		bool const isOver();

		void gameLoop();
	};
}

