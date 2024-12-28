//  TOURENNE    FERRY
//  Vincent     Antonny

#pragma once
#include <utility>
#include "token.h"

namespace kpt
{
	enum enum_cell { EMPTY, FOREST, RIVER };

	class cell
	{
		const std::pair<int, int> coords;
		const enum_cell type;
		const token* t_token;
		const flag* f_flag;
	public:
		cell();
		cell(const cell& other);
		~cell();
		cell& operator=(const cell& other);

		cell(const std::pair<int, int>& coords, const enum_cell& type, const token*& t_token, const flag* f_flag);
	};
}