//  TOURENNE    FERRY
//  Vincent     Antony

#include "../headers/Player.h"

#include <algorithm>

namespace kpt
{
    Player::Player(const std::string& name, const std::vector<std::pair<enum_token, std::pair<int, int>>>& tokens, const std::pair<int, int>& f_flag)
        : name(name), f_flag(flag(name, f_flag))
    {

        std::string player_num = std::string(1, name[1]);

        for (const std::pair<enum_token, std::pair<int, int>>& t : tokens)
        {
            switch (t.first)
            {
            case SCOUT:
                this->tokens.emplace_back(new scout("S" + player_num, t.second, *this));
                break;
            case ELITE:
                this->tokens.emplace_back(new elite("E" + player_num, t.second, *this));
                break;
            case FODDER:
                this->tokens.emplace_back(new fodder("F" + player_num, t.second, *this));
                break;
            default:
                break;
            }
        }
    }
}
