//  TOURENNE    FERRY
//  Vincent     Antony

#pragma once
#include <stdexcept>
#include <utility>
#include <vector>
#include "cell.h"

namespace kpt
{
	// Classe générique
	template <int width, int height>
	class T_Board
	{
		std::vector<cell> cells;	// Plateau (vecteur de cases)

	public:
		// Constructeurs
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

		// Getters & Setters
		std::pair<int, int> const getDimensions() const
		{
			return std::make_pair(width, height);
		}

		int const getWidth() const { return width; }
		int const getHeight() const { return height; }

		// Méthodes
		// Place un token dans une case
		void setToken(const std::pair<int, int>& pos, token* t) {
			cell* c = seek(pos);
			if (c) c->setToken(t);
		}

		// Place un flag dans une case
		void setFlag(const std::pair<int, int>& pos, flag* f) {
			cell* c = seek(pos);
			if (c) c->setFlag(f);
		}

		// Cherche une case à partir de ses coordonnées
		cell* seek(const std::pair<int, int>& pos)
		{
			if (pos.first < 0 || pos.first >= width || pos.second < 0 || pos.second >= height)
				throw std::out_of_range("Position out of board boundaries");
			else
				return &cells[pos.first+pos.second*height];
		}

		// Cherche une case en lecture seule
		const cell* seek(const int& posx, const int& posy) const
		{
			if (posx < 0 || posx >= width || posy < 0 || posy >= height)
				throw std::out_of_range("Position out of board boundaries");
			else
				return &cells[posx + posy * height];
		}
		
		// Vérifie si une position est hors du plateau
		bool const outOfBonds(std::pair<int, int> pos) const
		{
			return (pos.first < 0 || pos.second < 0 || pos.first >= getWidth() || pos.second >= getHeight());
		}

		// Cherche une cellule vide parmi une liste de positions
		std::pair<int, int> const searchEmptyCell(const std::vector<std::pair<int, int>> locations) const {
			for (const std::pair<int, int>& pos : locations) {
				if (outOfBonds(pos))
					continue;
				else if (seek(pos.first, pos.second)->isEmpty())
					return pos;
			}
			// Si on ne trouve pas, on renvoie une position non valide
			return std::make_pair(-1, -1);
		}

		// Retourne une liste de tous les flags présents sur le plateau
		std::vector<flag*> seekFlags() {
			std::vector<flag*> flags;
			for (cell& c : cells) {
				if (c.getFlag() != nullptr) flags.push_back(c.getFlag());
			}
			return flags;
		}

		// Réinitialise le flag donné à sa position d'origine
		void resetFlag(flag* f) {
			cell* currentCell = seek(f->getPosition());
			cell* originCell = seek(f->getOrigin());
			currentCell->loseFlag();
			originCell->setFlag(f);
		}
	};

	// Classe dérivée à dimensions fixes (10x10)
	class Board : public T_Board<10, 10> {
		public:
			// Constructeurs
			explicit Board() : T_Board() {}

			explicit Board(const std::vector<enum_cell>& cells)
				: T_Board(cells)
			{
			}

			// Retourne les cases adjacentes en fonction de la position et du joueur
			static std::vector<std::pair<int, int>> const getAdjacents(const std::pair<int, int>& pos, const std::string& player_name)
			{
				std::vector<std::pair<int, int>> adj;
				int x = pos.first;
				int y = pos.second;

				if (player_name == "P2") {
					adj.push_back(std::make_pair(x + 1, y));
					adj.push_back(std::make_pair(x + 1, y + 1));
					adj.push_back(std::make_pair(x + 1, y - 1));
				}
				else {
					adj.push_back(std::make_pair(x - 1, y));
					adj.push_back(std::make_pair(x - 1, y + 1));
					adj.push_back(std::make_pair(x - 1, y - 1));
				}

				return adj;
			}
	};
}