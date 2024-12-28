//  TOURENNE    FERRY
//  Vincent     Antonny

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

		// Méthodes à redéfinir
		virtual void battle(token& other) = 0;
		virtual void takeFlag(const flag& f_flag) = 0;

	protected:
		void assignFlag(const flag& f_flag) {
			this->f_flag = &f_flag;
		}
	};

	class scout : public token {
	public:
		scout(const std::string& name, const std::pair<int, int>& origin, const Player& owner)
			: token(SCOUT, name, 5, origin, owner) {}

		void battle(token& other) override {
			// TO DO : un des combattants a un flag
			switch (other.getType())
			{
			case SCOUT:
				// Rien ne se passe
				break;
			case ELITE:
				// this perd
				break;
			case FODDER:
				// this perd
				break;
			default:
				break;
			}
		}

		void takeFlag(const flag& f_flag) override {
			// Rien ne se passe !
		}
	};

	class elite : public token {
	public:
		elite(const std::string& name, const std::pair<int, int>& origin, const Player& owner)
			: token(ELITE, name, 3, origin, owner) {}

		void battle(token& other) override {
			// TO DO : un des combattants a un flag
			switch (other.getType())
			{
			case SCOUT:
				// other perd
				break;
			case ELITE:
				// les deux reculent d'une case. Si pas possible, alors perd
				break;
			case FODDER:
				// fodder perd
				break;
			default:
				break;
			}
		}

		void takeFlag(const flag& f_flag) override {
			assignFlag(f_flag);
		}
	};

	class fodder : public token {
	public:
		fodder(const std::string& name, const std::pair<int, int>& origin, const Player& owner)
			: token(FODDER, name, 2, origin, owner) {}

		void battle(token& other) override {
			// TO DO : un des combattants a un flag
			switch (other.getType())
			{
			case SCOUT:
				// other perd
				break;
			case ELITE:
				// this perd
				break;
			case FODDER:
				// 50/50 this ou other perd
				break;
			default:
				break;
			}
		}

		void takeFlag(const flag& f_flag) override {
			assignFlag(f_flag);
		}
	};
}