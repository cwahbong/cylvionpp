#ifndef CYLVIONPP_INTERNAL_SUPPORT_H
#define CYLVIONPP_INTERNAL_SUPPORT_H

#include "ravage.h"

namespace cylvionpp {

class SupportCard: public RavageCard {
    unsigned GetStrength() const override;

    bool IsBlazing() const override;
    void SetBlaze() override;

    bool OnBeforeMove(Dealer & dealer, const Actor & actor, const Location & location) const override final;

private:
    virtual bool OnBeforeMoveEffect(Dealer & dealer, const Actor & actor, const Location & location) const = 0;
};

} // namespace cylvionpp

#endif // CYLVIONPP_INTERNAL_SUPPORT_H
