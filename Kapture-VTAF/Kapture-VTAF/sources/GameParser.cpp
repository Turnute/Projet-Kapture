//  TOURENNE    FERRY
//  Vincent     Antony

#include "../headers/GameParser.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace kpt
{
	GameParser::GameParser(const std::string& filePath)
		: player_names(), player_tokens(2), flag_locations(2)
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
		int currentPlayer = 0;

		// Construction du plateau
		while (
			std::getline(file, line)	// On lit bien une ligne valide
			&& !line.empty()			// La ligne n'est pas vide
			&& line[0] != 'P'			// On est pas sur la définition d'un joueur
			)
		{
			std::stringstream ss(line);
			std::string cell;

			while (std::getline(ss, cell, ';')) {
				if (!cell.empty()) {
					cell_types.push_back(parseCell(cell));
				}
			}
		}

		// Construction des joueurs
		while (std::getline(file, line))
		{
			// Skip les lignes vides
			if (line.empty())
				continue;

			// Ligne annonçant un nouveau joueur
			if (line[0] == 'P')
			{
				currentPlayer = line[1] - '0';
				player_names.push_back("P" + std::to_string(currentPlayer));
				continue;
			}

			// Gestion des tokens et du flag
			parsePlayerLine(line, currentPlayer);
		}
	}
	std::vector<enum_cell> const GameParser::getCells()
	{
		return cell_types;
	}
	std::string const GameParser::getPlayerName(const int& i)
	{
		return player_names.at(i);
	}
	std::vector<std::pair<enum_token, std::pair<int, int>>> const GameParser::getPlayerTokens(const int& i)
	{
		return player_tokens.at(i);
	}
	std::pair<int, int> const GameParser::getPlayerFlag(const int& i)
	{
		return flag_locations.at(i);
	}
	
	enum_cell const GameParser::parseCell(const std::string& str)
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
	enum_token const GameParser::parseToken(const std::string& str)
	{
		if (str == "scout")
			return enum_token::SCOUT;
		else if (str == "elite")
			return enum_token::ELITE;
		else if (str == "fodder")
			return enum_token::FODDER;
		else
			throw std::runtime_error("Invalid cell type " + str);
	}
	std::pair<int, int> const GameParser::parsePosition(const std::string& str)
	{
		// On suppose que la position est donnée sous la forme :
		// PosX:PosY

		std::stringstream ss(str);
		std::string x, y;

		std::getline(ss, x, ':');
		std::getline(ss, y);

		return std::make_pair<int, int>(std::stoi(x), std::stoi(y));
	}
	
	void GameParser::parsePlayerLine(const std::string& line, const int& player)
	{
		size_t endType = line.find(':');
		std::string strType = line.substr(0, endType);
		std::string positions = line.substr(endType + 2);

		// Si c'est un Flag
		if (strType == "flag")
		{
			// Retire le ";" final
			if (positions.back() == ';')
				positions.pop_back();

			flag_locations.at(player - 1) = parsePosition(positions);
			return;
		}

		// Ligne listant les unités d'un type
		enum_token currentType = parseToken(strType);
		std::stringstream ss(positions);
		std::string pos;
		while (std::getline(ss, pos, ';'))
		{
			if (!pos.empty())
			{
				std::pair<int, int> position = parsePosition(pos);
				player_tokens.at(player - 1).push_back(std::make_pair(currentType, position));
			}
		}
	}
}