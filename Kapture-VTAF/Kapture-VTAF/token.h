//  TOURENNE    FERRY
//  Vincent     Antonny

#pragma once
#include <string>
#include "flag.h"
#include "Player.h"
#include <memory>

namespace kpt
{
	enum enum_token { SCOUT, ELITE, FODDER };

	class token {
		const enum_token type;				// Type du token
		const std::string name;				// Nom pour l'affichage
		const int max_travel;				// Points max de déplacement
		int curr_travel;					// Points actuels
		const std::pair<int, int> origin;	// Position d'origine
		flag* f_flag;						// Drapeau (peut être nullptr)
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
		const std::string& getName() const { return name; }
		const Player& getOwner() const { return owner; }
		flag* getFlag() const { return f_flag; }

		// Méthodes à redéfinir
		virtual void battle(token& other) = 0;
		virtual void takeFlag(const flag& f_flag) = 0;


	};

	class scout : public token {
	public:
		scout(const std::string& name, const std::pair<int, int>& origin, const Player& owner)
			: token(SCOUT, name, 5, origin, owner) {}

		void battle(token& other) override {
			// TODO
		}

		void takeFlag(const flag& f_flag) override {
			// TODO
		}
	};

	class elite : public token {
	public:
		elite(const std::string& name, const std::pair<int, int>& origin, const Player& owner)
			: token(ELITE, name, 3, origin, owner) {}

		void battle(token& other) override {
			// TODO
		}

		void takeFlag(const flag& f_flag) override {
			// TODO
		}
	};

	class fodder : public token {
	public:
		fodder(const std::string& name, const std::pair<int, int>& origin, const Player& owner)
			: token(FODDER, name, 2, origin, owner) {}

		void battle(token& other) override {
			// TODO
		}

		void takeFlag(const flag& f_flag) override {
			// TODO
		}
	};
}

