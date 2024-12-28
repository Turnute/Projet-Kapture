//  TOURENNE    FERRY
//  Vincent     Antony

#pragma once
#include <vector>
#include <utility>
#include "cell.h"

namespace kpt
{
	template <int x, int y> class Board
	{
		std::vector<std::vector<cell>> cells;	// Plateau (vector de vector de cases)
	public:
		Board(const std::vector<std::pair<enum_cell, std::pair<int, int>>>& cells);

		cell* seek(const std::pair<int, int>& pos);
	};
}

