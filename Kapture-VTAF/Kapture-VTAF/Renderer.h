//  TOURENNE    FERRY
//  Vincent     Antonny

#pragma once
#include <vector>
#include "Board.h"
#include "Player.h"

namespace kpt
{
	class Renderer
	{
		const std::vector<Player*> players;
		//const Board<int, int>& board;
	public:
		Renderer(const std::vector<Player*>& players/*const Board<int, int>& board*/);
		void const render();
	};
}

