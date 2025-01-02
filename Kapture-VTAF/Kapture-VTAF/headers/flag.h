//  TOURENNE    FERRY
//  Vincent     Antony

#pragma once
#include <utility>
#include <string>

namespace kpt
{
	class flag
	{
		const std::string name;				// Nom pour l'affichage
		const std::pair<int, int> origin;	// Coordonnées d'origine
		std::pair<int, int> position;		// Position
		bool isDropped;						// Check si on a été lâché ou non
		int cmpt;							// Compteur

	public:
		flag(const std::string& player_name, const std::pair<int, int>& origin);
		void drop();	// Met le flag en état "lâché"
		bool update();	// Méthode de mise à jour

		const std::pair<int, int> getPosition() const { return position; }
		flag& operator=(const flag& other)
		{
			if (this == &other) return *this;
			this->position = other.position;
			this->isDropped = other.isDropped;
			this->cmpt = other.cmpt;
			//TODO jsp si faut copier le nom aussi vu qu'il est constant
			return *this;
		}

		void setPosition(const std::pair<int, int>& pos);

		// Affichage
		friend std::ostream& operator<<(std::ostream& out, const flag& flag);
	};
}