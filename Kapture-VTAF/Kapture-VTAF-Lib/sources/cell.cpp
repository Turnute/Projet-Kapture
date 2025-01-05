//  TOURENNE    FERRY
//  Vincent     Antony

#include "../headers/cell.h"
#include <ostream>

namespace kpt
{
    // Constructeurs & destructeur
    cell::cell(
        const std::pair<int, int>& coords,
        const enum_cell& type,
        token* t_token,
        flag* f_flag
    ) :
        coords(coords),
        type(type),
        t_token(t_token),
        f_flag(f_flag) {}

    cell::cell(const cell& other) :
        coords(other.coords),
        type(other.type),
        t_token(other.t_token),
        f_flag(other.f_flag) {}

    cell::~cell() {}

    // Méthodes
    bool const cell::isEmpty() const
    {
        return (t_token == nullptr && f_flag == nullptr);
    }

    void cell::moveTokenTo(cell* cell)
    {
        this->t_token->setPosition(
            std::make_pair(cell->coords.second, cell->coords.first)
        );
        cell->t_token = this->t_token;
        this->t_token = nullptr;
    }

    // Affichage
    std::ostream& operator<<(std::ostream& out, const cell& cell)
    {
        if (cell.t_token)
            out << *(cell.t_token);
        else if (cell.f_flag)
            out << *(cell.f_flag);
        else
        {
            switch (cell.type)
            {
            case FOREST:
                out << " T ";
                break;
            case RIVER:
                out << " = ";
                break;
            case EMPTY:
                out << "   ";
                break;
            default:
                break;
            }
        }

        return out;
    }
}