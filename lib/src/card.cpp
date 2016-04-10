#include "cylvionpp/card.h"

namespace cylvionpp {

Card::~Card() = default;

bool
operator==(const Card & lhs, const Card & rhs)
{
    return lhs.GetName() == rhs.GetName();
}

bool
operator!=(const Card & lhs, const Card & rhs)
{
    return !(lhs == rhs);
}

} // namespace cylvionpp
