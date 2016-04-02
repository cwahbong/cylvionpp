#ifndef CYLVIONPP_CARD_H
#define CYLVIONPP_CARD_H

#include "cylvionpp_export.h"

#include <memory>

namespace cylvionpp {

class Actor;
class Dealer;

class CYLVIONPP_EXPORT Card {
public:
    virtual ~Card() = 0;

    virtual unsigned GetCost() const = 0;
    virtual unsigned GetStrength() const = 0;
    virtual unsigned GetVitality() const = 0;
    virtual unsigned GetPriority() const = 0;

    virtual bool IsCylvan() const = 0;
    virtual bool IsRavage() const = 0;
    virtual bool IsBlazing() const = 0;
    virtual bool IsNone() const = 0;

    virtual void SetBlaze() = 0;

    virtual bool OnBeforeMove(Dealer & dealer, const Actor & actor, size_t row, size_t col) const = 0;
    virtual bool OnUseWhenReveal(Dealer & dealer, const Actor & actor, size_t idx) const = 0;
    virtual bool OnUseWhenDefend(Dealer & dealer, const Actor & actor, size_t idx) const = 0;
};

} // namespace cylvionpp

#endif // CYLVIONPP_CARD_H
