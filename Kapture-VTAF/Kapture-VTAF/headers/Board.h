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

		void setToken(const std::pair<int, int>& pos, token* t) {
			cell* c = seek(pos);
			if (c) c->setToken(t);
		}
		void setFlag(const std::pair<int, int>& pos, flag* f) {
			cell* c = seek(pos);
			if (c) c->setFlag(f);
		}

		int const getWidth() const { return width; }
		int const getHeight() const { return height; }

		bool const outOfBonds(std::pair<int, int> pos) const
		{
			return (pos.first < 0 || pos.second < 0 || pos.first >= getWidth() || pos.second >= getHeight());
		}

		// Search for an empty cell within a list of positions
		std::pair<int, int> const searchEmptyCell(const std::vector<std::pair<int, int>> locations) const {
			for (const std::pair<int, int>& pos : locations) {
				if (outOfBonds(pos))
					continue;
				else if (seek(pos.first, pos.second)->isEmpty())
					return pos;
			}
			return std::make_pair(-1, -1);
		}

		std::vector<flag*> seekFlags() {
			std::vector<flag*> flags;
			for (cell& c : cells) {
				if (c.getFlag() != nullptr) flags.push_back(c.getFlag());
			}
			return flags;
		}

		void resetFlag(flag* f) {
			cell* currentCell = seek(f->getPosition());
			cell* originCell = seek(f->getOrigin());
			currentCell->loseFlag();
			originCell->setFlag(f);
		}
	};

	class Board : public T_Board<10, 10> {
		public:
			explicit Board() : T_Board() {}

			explicit Board(const std::vector<enum_cell>& cells)
				: T_Board(cells)
			{
			}

		static std::vector<std::pair<int, int>> const getAdjacents(const std::pair<int, int>& pos)
        {
			std::vector<std::pair<int, int>> adj;
			return adj;
			// TODO :
			// pos = X,Y
			// SI c'est le joueur 1, alors on renvoie la liste : "(X-1,Y);(X-1,Y-1);(X-1,Y+1)"
			// SI c'est le joueur 2, alors on renvoie la liste : "(X+1,Y);(X+1,Y+1);(X+1,Y-1)"
        }
	};
}