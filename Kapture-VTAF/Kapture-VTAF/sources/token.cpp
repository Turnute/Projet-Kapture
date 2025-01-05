//  TOURENNE    FERRY
//  Vincent     Antony
#include "../headers/token.h"
#include "../headers/Player.h"
#include <ostream>


namespace kpt
{
    // TOKEN METHODES ======================
    void token::dropFlag()
    {
        if (f_flag != nullptr) {
            f_flag->setPosition(position);
            f_flag->drop();
            f_flag = nullptr;
        }
    }

    bool token::isOwnedBy(const Player& player) const
    {
        return player == this->owner;
    }

    void token::assignFlag(flag& f_flag)
    {
        this->f_flag = &f_flag;
    }

    // SCOUT METHODES ======================
    int scout::battle(const token& other) {
        if (other.getType() == SCOUT || other.hasFlag())
            return 0;
        return 2;
    }

    // ELITE METHODES ======================
    int elite::battle(const token& other) {
        if (this->hasFlag())
            return 2;
        if (other.getType() != ELITE || other.hasFlag())
            return 1;
        return 0;
    }

    void elite::takeFlag(flag& f_flag) {
        if (f_flag.getOwner() == getOwner().getName()) return;
        assignFlag(f_flag);
    }

    // FODDER METHODES ======================
    int fodder::battle(const token& other) {
        if (this->hasFlag() || other.getType() == ELITE)
            return 2;
        if (other.hasFlag() || other.getType() == SCOUT)
            return 1;
        return 0;
    }

    void fodder::takeFlag(flag& f_flag) {
        if (f_flag.getOwner() == getOwner().getName()) return;
        assignFlag(f_flag);
    }

    // Affichage
    std::ostream& operator<<(std::ostream& out, const token& token)
    {
        out << token.name;
        if (token.hasFlag())
            out << "*";
        else out << " ";

        return out;
    }
}

