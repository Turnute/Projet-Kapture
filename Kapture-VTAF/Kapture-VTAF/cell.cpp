//  TOURENNE    FERRY
//  Vincent     Antony

#include "cell.h"
#include <ostream>

namespace kpt
{
    std::ostream& kpt::operator<<(std::ostream& out, const cell& cell)
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