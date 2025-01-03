//  TOURENNE    FERRY
//  Vincent     Antony

#include "../headers/flag.h"
#include <ostream>

namespace kpt
{
	// On admet que les joueurs sont nommés P1 et P2
	flag::flag(const std::string& player_name, const std::pair<int, int>& origin)
		: name(player_name), origin(origin), position(origin), isDropped(false), cmpt(2) {}

	void flag::drop()
	{
		isDropped = true;
		cmpt = 2;
	}

	bool flag::update()
	{
		if (isDropped && cmpt == 0)
		{
			this->position = this->origin;
			this->isDropped = false;
			return true;
		}
		if (isDropped)
		{
			cmpt--;
			return false;
		}
		return false;
	}

	void flag::reset()
	{
		position = origin;
		isDropped = false;
	}

	void flag::setPosition(const std::pair<int, int>& pos)
	{
		position = pos;
	}

	std::ostream& operator<<(std::ostream& out, const flag& flag)
	{
		out << flag.name << " ";
		return out;
	}
}
