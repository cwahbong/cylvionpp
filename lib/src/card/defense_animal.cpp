#include "defense_animal.h"

namespace cylvionpp {

DefenseAnimalCard::DefenseAnimalCard(unsigned cost):
    AnimalCard(cost)
{/* Empty. */}

bool
DefenseAnimalCard::CanUseWhenReveal() const
{
    return false;
}

bool
DefenseAnimalCard::CanUseWhenDefend() const
{
    return true;
}

} // namespace cylvionpp
