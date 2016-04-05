#ifndef CYLVIONPP_INTERNAL_DEFENSE_ANIMAL_H
#define CYLVIONPP_INTERNAL_DEFENSE_ANIMAL_H

#include "animal.h"

namespace cylvionpp {

class DefenseAnimalCard: public AnimalCard {
public:
    DefenseAnimalCard(unsigned cost);

private:
    bool CanUseWhenReveal() const;
    bool CanUseWhenDefend() const;
};

} // namespace cylvionpp

#endif // CYLVIONPP_INTERNAL_DEFENSE_ANIMAL_H
