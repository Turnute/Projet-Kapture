//  TOURENNE    FERRY
//  Vincent     Antony

#pragma once
#include <utility>
#include "token.h"
#include "flag.h"

namespace kpt
{
	class cell;
	std::ostream& operator<<(std::ostream& out, const cell& cell);
	enum enum_cell { EMPTY, FOREST, RIVER };

	class cell
	{
		const std::pair<int, int> coords;	// Coordonnées de la case
		const enum_cell type;				// Type de la case
		token* t_token;				// Pion sur la case (peut être nullptr)
		flag* f_flag;					// Drapeau sur la case (peut être nullptr)

	public:
		cell() = delete;								// Constructeur par défaut interdit
		cell& operator=(const cell& other) = delete;	// Affectation interdite
		token* getToken() const { return t_token; }
		void moveTokenTo(cell* cell);

		cell(const std::pair<int, int>& coords, const enum_cell& type, token* t_token, flag* f_flag);
		cell(const cell& other);
		~cell();

		void setToken(token* t) { t_token = t; }
		void setFlag(flag* f) { f_flag = f; }

		flag* getFlag() const { return f_flag; }

		friend std::ostream& operator<<(std::ostream& out, const cell& cell);
	};
}