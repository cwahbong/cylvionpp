#include "animal.h"

namespace cylvionpp {

AnimalCard::AnimalCard(unsigned cost):
    CylvanCard(cost)
{/* Empty. */}

bool
AnimalCard::IsTree() const
{
    return false;
}

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
