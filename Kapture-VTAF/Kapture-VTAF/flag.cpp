//  TOURENNE    FERRY
//  Vincent     Antony

#include "flag.h"

namespace kpt
{
	flag::flag(const std::pair<int, int>& origin)
		: origin(origin), isDropped(false), cmpt(2) {}

	void flag::drop()
	{
		isDropped = true;
		cmpt = 2;
	}

	void flag::update()
	{
		if (isDropped && cmpt == 0)
		{
			// TODO : reset à la position initiale
		}
		else if (isDropped)
			cmpt--;
	}
}
