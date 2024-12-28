//  TOURENNE    FERRY
//  Vincent     Antony

#include "token.h"

void kpt::token::assignFlag(const flag& f_flag)
{
    this->f_flag = &f_flag;
}

int kpt::scout::battle(const token& other) {
    if (other.getType() == SCOUT || other.hasFlag())
        return 0;
    return 2;
}

int kpt::elite::battle(const token& other){
    if (this->hasFlag())
        return 2;
    if (other.getType() != ELITE || other.hasFlag())
        return 1;
    return 0;
}

void kpt::elite::takeFlag(const flag& f_flag) {
    assignFlag(f_flag);
}

int kpt::fodder::battle(const token& other) {
    if (this->hasFlag() || other.getType() == ELITE)
        return 2;
    if (other.hasFlag() || other.getType() == SCOUT)
        return 1;
    return 0;
}

void kpt::fodder::takeFlag(const flag& f_flag) {
    assignFlag(f_flag);
}