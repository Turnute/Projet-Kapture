//  TOURENNE    FERRY
//  Vincent     Antony

#pragma once
#include <stdexcept>
#include <vector>
#include <utility>
#include "cell.h"

namespace kpt
{
	template <int width, int height> class Board
	{
		std::vector<cell> cells;	// Plateau (vector de vector de cases)
	public:
		Board(const std::vector<enum_cell>& cells)
		{
			if (cells.size() != width * height) throw std::invalid_argument("Invalid number of cells");

			for (int x = 0; x < width; x++)
			{
				for (int y = 0; y < height; y++)
				{
					this->cells.emplace_back(std::pair<int, int>(x, y), cells[x + y * height], nullptr, nullptr);
				}
			}
		}

		cell* seek(const std::pair<int, int>& pos)
		{
			return &cells[pos.first+pos.second*height];
		}
	};
}

