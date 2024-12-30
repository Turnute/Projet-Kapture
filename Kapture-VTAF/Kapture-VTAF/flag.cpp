//  TOURENNE    FERRY
//  Vincent     Antony

#include "flag.h"
#include <ostream>

namespace kpt
{
	// On admet que les joueurs sont nommés P1 et P2
	flag::flag(const std::string& player_name, const std::pair<int, int>& origin)
		: name("F" + player_name[1]), origin(origin), isDropped(false), cmpt(2) {}

	void flag::drop()
	{
		isDropped = true;
		cmpt = 2;
	}

	void flag::update()
	{
		if (isDropped && cmpt == 0)
		{
			this->position = this->origin;
			this->isDropped = false;
		}
		else if (isDropped)
			cmpt--;
	}
	std::ostream& operator<<(std::ostream& out, const flag& flag)
	{
		out << flag.name << " ";
		return out;
	}
}
