#ifndef CYLVIONPP_INTERNAL_CYLVAN_H
#define CYLVIONPP_INTERNAL_CYLVAN_H

#include "not_none.h"

namespace cylvionpp {

class CylvanCard: public NotNoneCard {
public:
    CylvanCard(unsigned cost);

    unsigned GetCost() const override;
    unsigned GetPriority() const override;

    bool IsCylvan() const override;
    bool IsRavage() const override;
    bool IsBlazing() const override;

    void SetBlaze() override;

    bool OnBeforeMove(Dealer &, const Actor &, const Location &) const override { return true; }
    bool OnUseWhenReveal(Dealer & content, const Actor & actor, Index) const override;
    bool OnUseWhenDefend(Dealer & content, const Actor & actor, Index) const override;

private:
    virtual bool CanUseWhenReveal() const = 0;
    virtual bool CanUseWhenDefend() const = 0;
    bool OnUse(Dealer & dealer, const Actor & actor, Index) const;
    virtual bool OnUseEffect(Dealer & dealer, const Actor & actor, Index) const = 0;

    unsigned _cost;
};

} // namespace cylvionpp

#endif // CYLVIONPP_INTERNAL_CYLVAN_H
