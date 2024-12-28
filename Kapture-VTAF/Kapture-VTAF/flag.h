//  TOURENNE    FERRY
//  Vincent     Antony

#pragma once
#include <utility>

namespace kpt
{
	class flag
	{
		const std::pair<int, int> origin;	// Coordonnées d'origine
		std::pair<int, int> position;		// Position
		bool isDropped;						// Check si on a été lâché ou non
		int cmpt;							// Compteur

	public:
		flag(const std::pair<int, int>& origin);
		void drop();	// Met le flag en état "lâché"
		void update();	// Méthode de mise à jour
	};
}