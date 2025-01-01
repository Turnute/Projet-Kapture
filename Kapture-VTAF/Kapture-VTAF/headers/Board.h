//  TOURENNE    FERRY
//  Vincent     Antony

#pragma once
#include <stdexcept>
#include <utility>
#include <vector>

#include "cell.h"

namespace kpt
{
	template <int width, int height> class T_Board
	{
		std::vector<cell> cells;	// Plateau (vector de vector de cases)
	public:
		T_Board() : cells() {}

		T_Board(const std::vector<enum_cell>& cells)
		{
			if (cells.size() != width * height) 
				throw std::invalid_argument("Invalid number of cells");

			for (int x = 0; x < width; x++)
			{
				for (int y = 0; y < height; y++)
				{
					this->cells.emplace_back(
						std::pair<int, int>(x, y), 
						cells[x + y * height], 
						nullptr, 
						nullptr
					);
				}
			}
		}

		std::pair<int, int> const getDimensions() const
		{
			return std::make_pair(width, height);
		}

		cell* seek(const std::pair<int, int>& pos)
		{
			if (pos.first < 0 || pos.first >= width || pos.second < 0 || pos.second >= height)
				throw std::out_of_range("Position out of board boundaries");
			else
				return &cells[pos.first+pos.second*height];
		}

		const cell* seek(const int& posx, const int& posy) const
		{
			if (posx < 0 || posx >= width || posy < 0 || posy >= height)
				throw std::out_of_range("Position out of board boundaries");
			else
				return &cells[posx + posy * height];
		}
	};

	class Board : public T_Board<10, 10> {
		public:
			explicit Board() : T_Board() {}

			explicit Board(const std::vector<enum_cell>& cells)
				: T_Board(cells)
			{
			}
	};
}