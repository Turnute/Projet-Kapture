//  TOURENNE    FERRY
//  Vincent     Antonny

#pragma once
#include <vector>
#include "cell.h"
namespace kpt
{
	template <int x, int y> class Board
	{
		std::vector<std::vector<cell>> cells;
	public:
		Board(const std::vector<std::pair<enum_cell, std::pair<int, int>>>& cells);
	};
}

