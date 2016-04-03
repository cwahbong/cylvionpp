#include "cylvionpp/types.h"

namespace cylvionpp {

std::ostream &
operator<<(std::ostream & os, const Location & location)
{
    os << "(" << location.row << ", " << location.col << ")";
    return os;
}

} // namespace cylvionpp
