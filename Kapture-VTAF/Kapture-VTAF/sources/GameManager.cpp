//  TOURENNE    FERRY
//  Vincent     Antony

#include "../headers/GameManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace kpt
{
	GameManager::GameManager(const std::string& filePath)
		: currentPlayerindex(0)
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
		for (Player& player : players) {
			for (token* token : player.getTokens()) {
				board.setToken(token->getPosition(), token);
				checkSurroundings(token->getPosition());
			}
			board.setFlag(player.getFlag().getPosition(), &player.getFlag());
		}

		// Création du renderer
		renderer = Renderer(this->players, this->board);
	}

	void GameManager::battle(token& t1, token& t2)
	{
		std::cout << "Battle initiated between "
			<< t1 << " & " << t2
			<< std::endl;
		if (t1.getOwner() == t2.getOwner())
			return;
		else
		{
			// Déterminer quel token appartient à quel joueur
			token* player1Token = nullptr;
			token* player2Token = nullptr;

			if (t1.isOwnedBy(players[0])) {
				player1Token = &t1;
				player2Token = &t2;
			}
			else {
				player1Token = &t2;
				player2Token = &t1;
			}

			switch (t1.battle(t2))
			{
			// Égalité : comportement dépendant du type
				std::cout << "Tie!" << std::endl;
			case 0:
				switch (t1.getType())
				{
				case SCOUT:
					// On en fait rien
					break;
				case ELITE:
				{
					// Les deux unités reculent d'une case (si possible)

					std::vector<std::pair<int, int>> possiblePos1 = Board::getAdjacents(t1.getPosition());
					std::vector<std::pair<int, int>> possiblePos2 = Board::getAdjacents(t2.getPosition());

					// Chercher une case libre pour chaque token
					std::pair<int, int> newPos1 = board.searchEmptyCell(possiblePos1);
					std::pair<int, int> newPos2 = board.searchEmptyCell(possiblePos2);

					// Déplacer les tokens
					if (newPos1.first != -1)
					{
						moveToken(player1Token->getPosition(), newPos1);
					}

					if (newPos2.second != -1)
						moveToken(player2Token->getPosition(), newPos2);
					break;
				}
				case FODDER:
				{
					// Chance aléatoire que l'un ou l'autre recule

					int randomNb = rand() % 2;
					if (randomNb == 0)
						resetToken(t1);
					else resetToken(t2);
					break;
				}
				}
				break;

			// Le joueur 1 gagne
			case 1:
				std::cout << "Player 1 Wins!" << std::endl;
				resetToken(*player2Token);
			// Le joueur 2 gagne
			case 2:
				std::cout << "Player 2 Wins!" << std::endl;
				resetToken(*player1Token);
			default:
				break;
			}
		}
	}
	void GameManager::resetToken(token& t_token)
	{
		std::pair<int, int> location = t_token.getPosition();

		if (t_token.hasFlag())
		{
			// Transfère la propriété du flag du token à la case, et initie son compteur.
			board.seek(location)->setFlag(t_token.getFlag());
			t_token.dropFlag();
		}

		moveToken(location, t_token.getOrigin());
		
		display();
	}

	void GameManager::moveToken(const std::pair<int, int>& token, const std::pair<int, int>& destination)
	{
		if (token == destination)
			std::cout << "Vous ne pouvez pas bouger ici !" << std::endl;
		else
		{
			board.moveToken(token, destination);
			checkSurroundings(destination);
		}
	}

	void GameManager::checkSurroundings(std::pair<int, int> position)
	{
		// Vérifie qu'on est sur la case d'un pion
		const cell* currentCell = board.seek(position.first, position.second);
		token* currentToken = currentCell->getToken();
		if (currentToken == nullptr) return;

		for (int x = -1; x <= 1; x++)
		{
			for (int y = -1; y <= 1; y++)
			{
				// Calcule la nouvelle position à checker
				int newX = position.first + x;
				int newY = position.second + y;
				std::pair<int, int> newPos(newX, newY);

				// Vérifie que les coordonnées sont valides
				if ((board.outOfBonds(newPos)))
					continue;

				// Rajoute la case à la liste de visite du joueur associé
				std::cout << "Updating cell " << newX << "." << newY << std::endl;
				currentToken->getOwner().addVisitedCell(newPos);

				// Gère le contenu de la case
				const cell* c = board.seek(newX, newY);
				token* token = c->getToken();

				if (x == 0 && y == 0) continue;

				if (c->getFlag() != nullptr)
				{
					token->takeFlag(*c->getFlag());
					//c->getFlag()
				}
				else if (token != nullptr) battle(*currentToken, *token);
			}
		}
	}

	std::pair<int, int> GameManager::askCoordinates(const std::string& message) {
		std::pair<int, int> coords;

		while (true) {
			std::cout << message;
			std::string input;
			std::cin >> input; // Lire une entrée unique
			std::stringstream ss(input);

			std::string first, second;

			// Extraire les deux parties séparées par une virgule
			if (std::getline(ss, first, ',') && std::getline(ss, second)) {
				// Convertir les parties en entiers
				coords.first = std::stoi(first);
				coords.second = std::stoi(second);

				if (!board.outOfBonds(coords))
				{
					// Si tout est valide, on quitte la boucle
					std::cout << "Je lis les coords : "
						<< coords.first << ","
						<< coords.second << std::endl;
					break;
				}
				else
					std::cout << "Valeurs incorrectes : veuillez entrer une position sur le plateau." << std::endl;
			}
			else {
				std::cout << "Format incorrect : veuillez entrer un position valide (ex : 3,4)." << std::endl;
			}
		}

		return coords;
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

		while (true)
		{
			display();

			std::string input;
			std::cout << "Que voulez-vous faire ? (move/endTurn) : ";
			std::cin >> input;

			if (input == "endTurn") break;
			if (input == "move")
			{
				std::pair<int, int> token;
				std::pair<int, int> destination;
				while (true)
				{
					token = askCoordinates("Coordonnées de l'unité à bouger : ");
					const kpt::token* token1 = board.seek(token)->getToken();
					if (token1 != nullptr && token1->isOwnedBy(player))
						break;
					std::cout << "Aucune unité à cet emplacement" << std::endl;
				}
				while (true)
				{
					destination = askCoordinates("Coordonnées de destination : ");
					if (abs(destination.first - token.first) <= 1 && abs(destination.second - token.second) <= 1)
						break;
					std::cout << "Destination invalide, veuillez choisir une case adjacente" << std::endl;
				}

				moveToken(token, destination);
			}

			for (flag* f : board.seekFlags())
			{
				if (f->update())
				{
					board.resetFlag(f);
					f->reset();
				}
			}

		}
	}

	bool const GameManager::isOver()
	{
		// Check si une unité avec un drapeau se trouve sur la ligne de l'adversaire
		return false;
	}

	void GameManager::gameLoop()
	{
		while (!isOver())
		{
			Player currentPlayer = players[currentPlayerindex];
			playerTurn(currentPlayer);
			currentPlayerindex = (currentPlayerindex + 1) % players.size();
		}
	}
}
