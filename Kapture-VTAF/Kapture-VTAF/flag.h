//  TOURENNE    FERRY
//  Vincent     Antonny

#pragma once
#include <utility>

namespace kpt
{
	class flag
	{
		const std::pair<int, int> origin;
		bool isDropped;
		int cmpt;
	public:
		flag(const std::pair<int, int>& origin);
		void update();
	};
}