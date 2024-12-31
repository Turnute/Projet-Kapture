//  TOURENNE    FERRY
//  Vincent     Antony

#include "GameManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace kpt
{
	GameManager::GameManager(const std::string& filePath)
	{
		// On suppose que le fichier lu suit le format suivant :
		// type_cell;type_cell;type_cell;type_cell... sur 10 lignes et 10 colonnes
		// 
		// P1
		// type_unite: posX:posY;posX:posY... sur 3 lignes
		// flag: posX:posY
		//
		// P2...

		// Initialisation
		std::ifstream file(filePath);
		if (!file.is_open())
			throw std::runtime_error("Unable to open file: " + filePath);

		std::string line;

		std::vector<enum_cell> cells;

		int currentPlayer = 0;
		std::vector<std::string> player_names;
		std::vector<std::vector<std::pair<enum_token, std::pair<int, int>>>> player_tokens;
		std::vector<std::pair<int, int>> player_flags;

		// Construction du plateau
		while (
			std::getline(file, line)	// On lit une ligne valide
			&& !line.empty()			// La ligne n'est pas vide
			&& line[0] != 'P'			// On ne passe pas à la définition d'un joueur
			) 
		{
			std::stringstream ss(line);
			std::string cell;

			while (std::getline(ss, cell, ';')) {
				if (!cell.empty()) {
					cells.push_back(parseCell(cell));
				}
			}
		}

		board = Board(cells);

		// Construction des joueurs
		while (std::getline(file, line))
		{
			if (line.empty())
				continue;

			if (line[0] == 'P')
			{

			}
		}
	}

	enum_cell const GameManager::parseCell(const std::string& str)
	{
		if (str == "empty")
			return enum_cell::EMPTY;
		else if (str == "forest")
			return enum_cell::FOREST;
		else if (str == "river")
			return enum_cell::RIVER;
		else
			throw std::runtime_error("Invalid cell type " + str);
	}

	std::pair<int, int> const GameManager::parsePosition(const std::string& str)
	{
		// On suppose que la position est donnée sous la forme :
		// PosX:PosY

		std::stringstream ss(str);
		std::string x, y;

		std::getline(ss, x, ':');
		std::getline(ss, y);

		return std::make_pair<int, int>(std::stoi(x), std::stoi(y));
	}

	void GameManager::battle(token& t1, token& t2)
	{
		switch (t1.battle(t2))
		{
		case 0:
			switch (t1.getType())
			{
			case SCOUT:
				break;
			case ELITE:
				// TODO : Les deux reculent d'une case
				break;
			case FODDER:
				// TODO : 50/50 qui gagne ou perd
				break;
			}
			break;
		case 1:
			resetToken(t2);
		case 2:
			resetToken(t1);
		default:
			break;
		}
	}
	void GameManager::resetToken(token& t_token)
	{
		//TODO :
		// 
		// Drop le flag sur une case libre s'il en a un
			// Commence le compte du flag

		// Reset le token à sa position initiale
	}
}