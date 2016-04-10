#ifndef CYLVIONPP_INTERNAL_ON_FIELD_CYLVAN_H
#define CYLVIONPP_INTERNAL_ON_FIELD_CYLVAN_H

#include "cylvan.h"

namespace cylvionpp {

class OnFieldCylvanCard: public CylvanCard {
public:
    OnFieldCylvanCard(unsigned cost);

private:
    bool CanUseWhenReveal() const override;
    bool CanUseWhenDefend() const override;
    bool OnUseEffect(Dealer & dealer, const Actor & actor, Index idx) const override;
};

} // namespace cylvionpp

#endif // CYLVIONPP_INTERNAL_ON_FIELD_CYLVAN_H
