//  TOURENNE    FERRY
//  Vincent     Antony

#include "headers/GameManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace kpt
{
	/*TODO : c'est du pseudo code ici
	GameManager::GameManager(const std::string& filePath)
	{
		GameParser parser(filePath);
		board = Board(parser.getCells());

		Player p1 = Player(
			parser.getPlayerName(0),
			parser.getPlayerTokens(0), 
			parser.getPlayerFlag(0)
		);

		Player p2 = Player(
			parser.getPlayerName(1),
			parser.getPlayerTokens(1),
			parser.getPlayerFlag(1)
		);

		// Insertion des joueurs dans la map
		renderer = Renderer(players, board);
	}*/

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