//  TOURENNE    FERRY
//  Vincent     Antony

#include "headers/Player.h"

#include <algorithm>

namespace kpt
{
	Player::Player(const std::string& name, const std::vector<std::pair<enum_token, std::pair<int, int>>>& tokens, const std::pair<int, int>& f_flag)
		: name(name), f_flag(flag(name, f_flag))
	{
		std::vector<std::pair<enum_token, int>> ids;

		for (const std::pair<enum_token, std::pair<int, int>>& t : tokens)
		{
			std::string id_str = "";
			std::vector<std::pair<enum_token, int>>::iterator id = std::find_if(
				ids.begin(), ids.end(), 
				[&t](const std::pair<enum_token, int>& p) { return p.first == t.first; });

			if (id == ids.end())
			{
				ids.emplace_back(t.first, 1);
				id_str = "1";
			}
			else id_str = std::to_string(id->second++);


			switch (t.first)
			{
				case SCOUT:
					this->tokens.emplace_back(new scout("S"+id_str, t.second, *this));
					break;
				case ELITE:
					this->tokens.emplace_back(new elite("E"+id_str, t.second, *this));
					break;
				case FODDER:
					this->tokens.emplace_back(new fodder("F"+id_str, t.second, *this));
					break;
				default:
					break;
			}
		}
	}
}
