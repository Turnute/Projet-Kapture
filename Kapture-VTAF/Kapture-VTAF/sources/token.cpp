//  TOURENNE    FERRY
//  Vincent     Antony

#include "../headers/token.h"
#include <ostream>

namespace kpt
{
    bool token::isOwnedBy(const Player& player) const
    {
        return &player == &owner; //j'arrive pas à faire sans & donc pour l'instant on compare les adresses
    }

    void token::assignFlag(const flag& f_flag)
    {
        this->f_flag = &f_flag;
    }

    int scout::battle(const token& other) {
        if (other.getType() == SCOUT || other.hasFlag())
            return 0;
        return 2;
    }

    int elite::battle(const token& other) {
        if (this->hasFlag())
            return 2;
        if (other.getType() != ELITE || other.hasFlag())
            return 1;
        return 0;
    }

    void elite::takeFlag(const flag& f_flag) {
        assignFlag(f_flag);
    }

    int fodder::battle(const token& other) {
        if (this->hasFlag() || other.getType() == ELITE)
            return 2;
        if (other.hasFlag() || other.getType() == SCOUT)
            return 1;
        return 0;
    }

    void fodder::takeFlag(const flag& f_flag) {
        assignFlag(f_flag);
    }

    std::ostream& operator<<(std::ostream& out, const token& token)
    {
        out << token.name;
        if (token.hasFlag())
            out << "*";
        else out << " ";

        return out;
    }
}

