//  TOURENNE    FERRY
//  Vincent     Antony

#include "../headers/GameManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace kpt
{
	GameManager::GameManager(const std::string& filePath)
	{
		GameParser parser(filePath);

		board = Board(parser.getCells());

		// Création et stockage des joueurs
		players.reserve(2);
		players.emplace_back(
			parser.getPlayerName(0),
			parser.getPlayerTokens(0), 
			parser.getPlayerFlag(0));
		players.emplace_back(
			parser.getPlayerName(1),
			parser.getPlayerTokens(1),
			parser.getPlayerFlag(1));

		// Lien entre cells et token/flag
		for (const Player& player : players) {
			for (const token* token : player.getTokens()) {
				board.setToken(token->getPosition(), token);
			}
			board.setFlag(player.getFlag().getPosition(), &player.getFlag());
		}

		// Création du renderer
		renderer = Renderer(this->players, this->board);
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

	void GameManager::moveToken(const Player& owner, const std::pair<int, int>& token, const std::pair<int, int>& destination)
	{
		//bouge l'unité en gardant trace des cases visités
		// gère les points de mouvement
		// Appelle checkSurroundings et render()

	}

	void GameManager::checkSurroundings(const token& t_token)
	{
		// Regarde toutes les cases adjaçantes et :
		//	lance des combats s'il le faut
		//	récupére un drapeau s'il est là
		//	met à jour les cases visités du joueur (fog)
	}

	void GameManager::playerTurn(const Player& player)
	{
		// Garde une trace de toutes les unités ayant bougé ce tour-ci
		// -> Boucle while
		// render()
		// Demande au joueur son input ("move" ou "endTurn")
		//	-> endTurn : sors de la boucle
		//	-> move : 
		//		- demande les coordonnées de l'unité à bouger
		//		- demande les coordonnées de destination (doit être case adjaçante)
		//		- appel de moveToken sur l'unité en question
	}

	bool const GameManager::isOver()
	{
		// Check si une unité avec un drapeau se trouve sur la ligne de l'adversaire
		return false;
	}

	void GameManager::gameLoop()
	{
		int currentPlayerindex = 0;
		while (!isOver())
		{
			Player currentPlayer = players[currentPlayerindex];
			playerTurn(currentPlayer);
			currentPlayerindex = (currentPlayerindex + 1) % players.size();
		}
	}
}
