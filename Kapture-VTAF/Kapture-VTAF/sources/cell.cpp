//  TOURENNE    FERRY
//  Vincent     Antony

#include "cell.h"
#include <ostream>

namespace kpt
{
    cell::cell(
        const std::pair<int, int>& coords, 
        const enum_cell& type, 
        const token* t_token, 
        const flag* f_flag
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

    std::ostream& operator<<(std::ostream& out, const cell& cell)
    {
        if (cell.t_token != nullptr)
            out << *(cell.t_token);
        else if (cell.f_flag != nullptr)
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