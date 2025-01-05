//  TOURENNE    FERRY
//  Vincent     Antony

#include "../headers/Player.h"
#include <algorithm>

namespace kpt
{
    // Constructeurs & Destructeur
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
    Player::Player(const Player& other) : name(other.name), f_flag(other.f_flag)
    {
        if (this == &other) return;
        for (token* t : other.tokens) {
            tokens.push_back(t);
        }
        for (std::pair<int, int> pair : other.visitedCells) {
            visitedCells.push_back(pair);
        }
    }
    Player::~Player()
    {
        for (token* t : tokens)
            delete t;
    }

    // Surcharge d'opérateurs
    Player& Player::operator=(const Player& other)
    {
        if (this == &other) return *this;
        for (token* t : other.tokens) {
            tokens.push_back(t);
        }
        for (std::pair<int, int> pair : other.visitedCells) {
            visitedCells.push_back(pair);
        }
        this->f_flag = other.f_flag;

        return *this;
    }
    bool Player::operator==(const Player& other) const
    {
        return this->name == other.name;
    }

    // Méthodes
    void Player::addVisitedCell(const std::pair<int, int>& pos)
    {
        if (std::find(visitedCells.begin(), visitedCells.end(), pos) == visitedCells.end()) {
            visitedCells.push_back(pos);
        }
    }
    bool Player::hasVisitedCell(int i, int j) const
    {
        return std::find(visitedCells.begin(), visitedCells.end(),
            std::make_pair(i, j)) != visitedCells.end();
    }
}
