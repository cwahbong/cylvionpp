#ifndef CYLVIONPP_INTERNAL_CARD_RAVAGE_H
#define CYLVIONPP_INTERNAL_CARD_RAVAGE_H

#include "not_none.h"

namespace cylvionpp {

class RavageCard: public NotNoneCard {
public:
    unsigned GetCost() const override { return 0; }
    unsigned GetVitality() const override { return 0; }

    bool IsCylvan() const override { return false; }
    bool IsTree() const override { return false; }
    bool IsRavage() const override { return true; }

    bool OnUseWhenReveal(Dealer &, const Actor &, Index) const override { throw std::logic_error("Ravage is not usable"); }
    bool OnUseWhenDefend(Dealer &, const Actor &, Index) const override { throw std::logic_error("Ravage is not usable"); }
};

} // namespace cylvionpp

#endif // CYLVIONPP_INTERNAL_CARD_RAVAGE_H
