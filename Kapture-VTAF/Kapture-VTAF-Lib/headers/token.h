//  TOURENNE    FERRY
//  Vincent     Antony

#pragma once
#include <string>
#include <utility>
#include "flag.h"

namespace kpt
{
	class Player;

	enum enum_token { SCOUT, ELITE, FODDER };

	class token {
		const enum_token type;				// Type du token
		const std::string name;				// Nom pour l'affichage
		const int max_travel;				// Points max de déplacement
		int curr_travel;					// Points actuels
		const std::pair<int, int> origin;	// Position d'origine
		std::pair<int, int> position;		// Position actuelle
		const Player& owner;				// Joueur propriétaire (référence constante)

	protected:
		flag* f_flag;						// Drapeau (peut être nullptr)
		void assignFlag(flag& f_flag);

	public:
		token() = delete;							// Constructeur par défaut interdit
		token(const token&) = delete;				// Copie interdite
		token& operator=(const token&) = delete;	// Affectation interdite

		// Constructeurs & Destructeur
		token(const enum_token& type, const std::string& name, 
			int max_travel, const std::pair<int, int>& origin, 
			const Player& owner
		) : type(type), name(name), 
			max_travel(max_travel), curr_travel(0), 
			origin(origin), position(origin), 
			f_flag(nullptr), owner(owner) {}

		virtual ~token() {
			f_flag = nullptr;
		}

		// Getters & Setters
		const enum_token getType() const { return type; }
		const std::string& getName() const { return name; }
		const int getMaxTravel() const { return max_travel; }
		int getCurrentTravel() const { return curr_travel; }
		const std::pair<int, int> getOrigin() const { return origin; }
		const std::pair<int, int> getPosition() const { return position;  }
		void setPosition(const std::pair<int, int> pos) { position = pos; }
		flag* getFlag() const { return f_flag; }
		Player& getOwner() { return const_cast<Player&>(owner); }

		// Méthodes
		bool hasFlag() const { return f_flag != nullptr; }
		void dropFlag();
		bool canMove() const { return curr_travel < max_travel; }
		void move() { curr_travel++; }
		void resetTravel() { curr_travel = 0; }
		bool isOwnedBy(const Player& player) const;

		// Méthodes à redéfinir
		virtual int battle(const token& other) = 0;	// Renvoie le résultat du combat (0 égalité, 1 victoire, 2 défaite)
		virtual void takeFlag(flag& f_flag) = 0;	// Prend le drapeau

		// Affichage
		friend std::ostream& operator<<(std::ostream& out, const token& token);
	};

	class scout : public token {
	public:
		scout(const std::string& name, const std::pair<int, int>& origin, const Player& owner)
			: token(SCOUT, name, 5, origin, owner) {}

		int battle(const token& other) override;

		void takeFlag(flag& f_flag) override {
			// Rien ne se passe !
		}
	};

	class elite : public token {
	public:
		elite(const std::string& name, const std::pair<int, int>& origin, const Player& owner)
			: token(ELITE, name, 3, origin, owner) {}

		int battle(const token& other) override;
		void takeFlag(flag& f_flag) override;
	};

	class fodder : public token {
	public:
		fodder(const std::string& name, const std::pair<int, int>& origin, const Player& owner)
			: token(FODDER, name, 2, origin, owner) {}

		int battle(const token& other) override;
		void takeFlag(flag& f_flag) override;
	};
}