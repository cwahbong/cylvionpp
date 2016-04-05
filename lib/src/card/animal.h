#ifndef CYLVIONPP_INTERNAL_ANIMAL_H
#define CYLVIONPP_INTERNAL_ANIMAL_H

#include "cylvan.h"

namespace cylvionpp {

class AnimalCard: public CylvanCard {
public:
    AnimalCard(unsigned cost);

    unsigned GetStrength() const;
    unsigned GetVitality() const;
};

} // namespace cylvionpp

#endif // CYLVIONPP_INTERNAL_ANIMAL_H
