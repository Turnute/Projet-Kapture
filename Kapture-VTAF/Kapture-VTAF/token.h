//  TOURENNE    FERRY
//  Vincent     Antony

#pragma once
#include <string>
#include <utility>
#include <vector>
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
		const flag* f_flag;					// Drapeau (peut être nullptr)
		const Player& owner;				// Joueur propriétaire (référence constante)

		token() = delete;							// Constructeur par défaut interdit
		token(const token&) = delete;				// Copie interdite
		token& operator=(const token&) = delete;	// Affectation interdite

	public:
		token(const enum_token& type, const std::string& name, int max_travel, const std::pair<int, int>& origin, const Player& owner)
			: type(type), name(name), max_travel(max_travel), curr_travel(0), origin(origin), f_flag(nullptr), owner(owner) {}

		virtual ~token() {
			f_flag = nullptr;
		}

		// Getters
		const enum_token getType() const { return type; }
		const std::string& getName() const { return name; }
		const Player& getOwner() const { return owner; }
		const flag* getFlag() const { return f_flag; }
		bool hasFlag() const { return f_flag != nullptr; }

		// Méthodes à redéfinir
		virtual int battle(const token& other) = 0;			// Renvoie le résultat du combat (0 égalité, 1 victoire, 2 défaite)
		virtual void takeFlag(const flag& f_flag) = 0;	// Prend le drapeau

	protected:
		void assignFlag(const flag& f_flag) {
			this->f_flag = &f_flag;
		}
	};

	class scout : public token {
	public:
		scout(const std::string& name, const std::pair<int, int>& origin, const Player& owner)
			: token(SCOUT, name, 5, origin, owner) {}

		int battle(const token& other) override {
			if (other.getType() == SCOUT || other.hasFlag())
				return 0;
			else return 2;
		}

		void takeFlag(const flag& f_flag) override {
			// Rien ne se passe !
		}
	};

	class elite : public token {
	public:
		elite(const std::string& name, const std::pair<int, int>& origin, const Player& owner)
			: token(ELITE, name, 3, origin, owner) {}

		int battle(const token& other) override {
			if (this->hasFlag())
				return 2;
			else if (other.getType() != ELITE || other.hasFlag())
				return 1;
			else return 0;
		}

		void takeFlag(const flag& f_flag) override {
			assignFlag(f_flag);
		}
	};

	class fodder : public token {
	public:
		fodder(const std::string& name, const std::pair<int, int>& origin, const Player& owner)
			: token(FODDER, name, 2, origin, owner) {}

		int battle(const token& other) override {
			if (this->hasFlag() || other.getType() == ELITE)
				return 2;
			else if (other.hasFlag() || other.getType() == SCOUT)
				return 1;
			else return 0;
		}

		void takeFlag(const flag& f_flag) override {
			assignFlag(f_flag);
		}
	};
}