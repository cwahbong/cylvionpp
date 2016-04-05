#include "animal.h"

namespace cylvionpp {

AnimalCard::AnimalCard(unsigned cost):
    CylvanCard(cost)
{/* Empty. */}

unsigned
AnimalCard::GetStrength() const
{
    return 0;
}

unsigned
AnimalCard::GetVitality() const
{
    return 0;
}

} // namespace cylvionpp
