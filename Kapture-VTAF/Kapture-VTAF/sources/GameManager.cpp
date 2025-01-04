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
		std::cout << "Combat initié entre "
			<< t1.getName() << " & " << t2.getName()
			<< "... ";

		// Récupère le résultat de la méthode de bataille
		int battleResult = t1.battle(t2);

		switch (battleResult)
		{
		case 0:	// Égalité 
			switch (t1.getType())
			{
			case SCOUT:
				std::cout << "Les éclaireurs s'évitent !" << std::endl;
				break;
			case ELITE:
			{
				std::cout << "Égalité entre les troupes d'élite !" << std::endl;
				// Les deux unités reculent d'une case (si possible)
				std::vector<std::pair<int, int>> possiblePos1 = Board::getAdjacents(t1.getPosition(), t1.getOwner().getName());
				std::vector<std::pair<int, int>> possiblePos2 = Board::getAdjacents(t2.getPosition(), t2.getOwner().getName());

				// Chercher une case libre pour chaque token
				std::pair<int, int> newPos1 = board.searchEmptyCell(possiblePos1);
				std::pair<int, int> newPos2 = board.searchEmptyCell(possiblePos2);

				// Déplacer les tokens si possible, sinon reset à l'origine
				if (newPos1.first != -1)
					moveToken(t1.getPosition(), newPos1);
				else
					resetToken(t1);

				if (newPos2.first != -1)
					moveToken(t2.getPosition(), newPos2);
				else
					resetToken(t2);

				break;
			}
			case FODDER:
			{
				std::cout << "Combat aléatoire entre chairs à canon !" << std::endl;
				if (rand() % 2 == 0) {
					std::cout << t1.getName() << " gagne !" << std::endl;
					resetToken(t2);
				}
				else {
					std::cout << t2.getName() << " gagne !" << std::endl;
					resetToken(t1);
				}
				break;
			}
			}
			break;

		case 1:	// T1 gagne
			std::cout << t1.getName() << " gagne !" << std::endl;
			resetToken(t2);
			break;
		case 2:	// T2 gagne
			std::cout << t2.getName() << " gagne !" << std::endl;
			resetToken(t1);
			break;
		}
	}

	void GameManager::resetToken(token& t_token)
	{
		std::pair<int, int> currentLocation = t_token.getPosition();
		std::pair<int, int> originLocation = t_token.getOrigin();

		// Gestion du drapeau si le token en porte un
		if (t_token.hasFlag())
		{
			flag* currentFlag = t_token.getFlag();
			board.seek(currentLocation)->setFlag(currentFlag);
			t_token.dropFlag();
		}

		// On s'assure que la cellule d'origine est libre
		cell* originCell = board.seek(originLocation);
		if (originCell->getToken() != nullptr) {
			std::cout << "Erreur : position d'origine occupée !" << std::endl;
			return;
		}

		board.seek(currentLocation)->moveTokenTo(originCell);
	}

	void GameManager::moveToken(const std::pair<int, int>& origin, const std::pair<int, int>& destination)
	{
		if (origin == destination) {
			std::cout << "Vous êtes déjà sur cette case !" << std::endl;
			return;
		}

		cell* originCell = board.seek(origin);
		cell* destCell = board.seek(destination);

		// Vérifie la présence d'un token à l'origine
		if (!originCell->getToken()) {
			std::cout << "Aucune unité à déplacer!" << std::endl;
			return;
		}

		// Vérifie que la destination est libre
		if (destCell->getToken()) {
			std::cout << "Case de destination déjà occupée!" << std::endl;
			return;
		}

		// Déplace le token
		originCell->moveTokenTo(destCell);
		checkSurroundings(destination);
	}

	void GameManager::checkSurroundings(std::pair<int, int> position)
	{
		// Vérifie qu'on est sur la case d'un pion
		const cell* currentCell = board.seek(position.first, position.second);
		token* currentToken = currentCell->getToken();
		if (currentToken == nullptr) return;

		// S'assure d'un seul combat par tour
		bool hasBattled = false;

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
				currentToken->getOwner().addVisitedCell(newPos);

				// Gère le contenu de la case
				cell* c = board.seek(newPos);
				token* token = c->getToken();

				if (x == 0 && y == 0) continue;

				if (c->getFlag() != nullptr)
				{
					if (c->getFlag()->getOwner() != currentToken->getOwner().getName()) {
						currentToken->takeFlag(*c->getFlag());
						if (currentToken->hasFlag()) {
							c->loseFlag();
						}
					}
				}
				else if (token != nullptr && !hasBattled)
				{
					if (!(currentToken->getOwner() == token->getOwner()))
					{
						battle(*currentToken, *token);
						hasBattled = true;  // Empêche d'autres combats pendant ce tour
					}
				}
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
		while (true)
		{
			display();

			std::string input;
			std::cout << "Que voulez-vous faire ? (move/endTurn) : ";
			std::cin >> input;

			if (input == "endTurn") break;
			else if (input == "move")
			{
				std::pair<int, int> token;
				std::pair<int, int> destination;
				while (true)
				{
					token = askCoordinates("Coordonnées de l'unité à bouger (Ligne,Colonne): ");
					const kpt::token* token1 = board.seek(token)->getToken();
					if (token1 != nullptr && token1->isOwnedBy(player))
						break;
					std::cout << "Aucune unité à cet emplacement" << std::endl;
				}
				while (true)
				{
					destination = askCoordinates("Coordonnées de destination (Ligne,Colonne) : ");
					if (abs(destination.first - token.first) <= 1 && abs(destination.second - token.second) <= 1)
						break;
					std::cout << "Destination invalide, veuillez choisir une case adjacente" << std::endl;
				}

				moveToken(token, destination);
			}
			else std::cout << "Input non valide !" << std::endl;
		}

		// Update les flags à la fin du tour
		std::vector<flag*> flags = board.seekFlags();
		for (flag* f : flags)
		{
			if (f->update())
			{
				// Pour chaque case du plateau, on vérifie si elle contient notre drapeau
				for (int x = 0; x < board.getWidth(); x++) {
					for (int y = 0; y < board.getHeight(); y++) {
						cell* currentCell = board.seek(std::make_pair(x, y));
						if (currentCell->getFlag() == f) {
							// On a trouvé le drapeau, on peut le retirer
							currentCell->loseFlag();
							break;
						}
					}
				}

				// On place le flag à sa position d'origine
				board.seek(f->getOrigin())->setFlag(f);
				f->reset();
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
			Player& currentPlayer = players[currentPlayerindex];
			playerTurn(currentPlayer);
			currentPlayerindex = (currentPlayerindex + 1) % players.size();
		}
	}
}
