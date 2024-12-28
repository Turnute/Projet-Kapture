//  TOURENNE    FERRY
//  Vincent     Antony

#include "Player.h"

namespace kpt
{
	Player::Player(const std::string& name, const std::vector<std::pair<enum_token, std::pair<int, int>>>& tokens, const std::pair<int, int>& f_flag)
		: name(name), f_flag(flag(f_flag))
	{
		// Création et stockage des tokens
	}
}