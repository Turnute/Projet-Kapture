//  TOURENNE    FERRY
//  Vincent     Antonny

#pragma once
#include <utility>
#include "token.h"
#include "flag.h"

namespace kpt
{
	enum enum_cell { EMPTY, FOREST, RIVER };

	class cell
	{
		const std::pair<int, int> coords;	// Coordonnées de la case
		const enum_cell type;				// Type de la case
		const token* t_token;				// Pion sur la case (peut être nullptr)
		const flag* f_flag;					// Drapeau sur la case (peut être nullptr)							

		cell() = delete;								// Constructeur par défaut interdit
		cell(const cell& other) = delete;				// Copie interdite
		cell& operator=(const cell& other) = delete;	// Affectation interdite
	public:

		cell(const std::pair<int, int>& coords, const enum_cell& type, const token& t_token, const flag& f_flag);
		~cell();
	};
}