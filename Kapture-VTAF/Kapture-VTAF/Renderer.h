//  TOURENNE    FERRY
//  Vincent     Antony

#pragma once
#include <vector>
#include "Board.h"
#include "Player.h"

namespace kpt
{
	class Renderer
	{
		const std::vector<Player*> players;	// Liste des joueurs
		//const Board<int, int>& board;		// Plateau
	public:
		Renderer(const std::vector<Player*>& players/*const Board<int, int>& board*/);
		void render() const;	// Affichage de l'état actuel de la partie
	};
}

