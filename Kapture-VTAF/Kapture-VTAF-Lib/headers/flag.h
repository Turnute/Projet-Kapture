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

		// Méthodes
		void drop();	// Met le flag en état "lâché"
		bool update();	// Méthode de mise à jour
		void reset();	// Méthode de reset

		// Getters & Setters
		const std::pair<int, int> getPosition() const { return position; }
		const std::pair<int, int> getOrigin() const { return origin; }
		const std::string& getOwner() const { return name; }
		void setPosition(const std::pair<int, int>& pos);

		// Surdéfinition d'Opérateurs
		flag& operator=(const flag& other);

		// Affichage
		friend std::ostream& operator<<(std::ostream& out, const flag& flag);
	};
}