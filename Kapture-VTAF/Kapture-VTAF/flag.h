//  TOURENNE    FERRY
//  Vincent     Antonny

#pragma once
#include <utility>

namespace kpt
{
	class flag
	{
		const std::pair<int, int> origin;	// Coordonnées d'origine
		bool isDropped;						// Check si on a été lâché ou non
		int cmpt;							// Compteur
	public:
		flag(const std::pair<int, int>& origin);
		void update();	// Méthode de mise à jour
	};
}