#ifndef CYLVIONPP_CARD_H
#define CYLVIONPP_CARD_H

#include "cylvionpp_export.h"
#include "types.h"

#include <memory>
#include <string>

namespace cylvionpp {

class Actor;
class Dealer;

class CYLVIONPP_EXPORT Card {
public:
    virtual ~Card() = 0;

    virtual std::string GetName() const = 0;

    virtual unsigned GetCost() const = 0;
    virtual unsigned GetStrength() const = 0;
    virtual unsigned GetVitality() const = 0;
    virtual unsigned GetPriority() const = 0;

    virtual bool IsCylvan() const = 0;
    virtual bool IsTree() const = 0;
    virtual bool IsRavage() const = 0;
    virtual bool IsBlazing() const = 0;
    virtual bool IsNone() const = 0;

    virtual void SetBlaze() = 0;

    virtual bool OnBeforeMove(Dealer & dealer, const Actor & actor, const Location & location) const = 0;
    virtual bool OnUseWhenReveal(Dealer & dealer, const Actor & actor, Index index) const = 0;
    virtual bool OnUseWhenDefend(Dealer & dealer, const Actor & actor, Index index) const = 0;

    CYLVIONPP_EXPORT friend bool operator==(const Card &, const Card &);
    CYLVIONPP_EXPORT friend bool operator!=(const Card &, const Card &);
};

namespace card {

CYLVIONPP_EXPORT std::unique_ptr<Card> None();
CYLVIONPP_EXPORT std::unique_ptr<Card> Fountain(unsigned cost, unsigned strength);
CYLVIONPP_EXPORT std::unique_ptr<Card> Tree(unsigned cost, unsigned vitality);
CYLVIONPP_EXPORT std::unique_ptr<Card> Whale();
CYLVIONPP_EXPORT std::unique_ptr<Card> Elephant();
CYLVIONPP_EXPORT std::unique_ptr<Card> Hedgehogs();
CYLVIONPP_EXPORT std::unique_ptr<Card> Owl();
CYLVIONPP_EXPORT std::unique_ptr<Card> Stag();
CYLVIONPP_EXPORT std::unique_ptr<Card> Doves();
CYLVIONPP_EXPORT std::unique_ptr<Card> Squirrels();
CYLVIONPP_EXPORT std::unique_ptr<Card> Fish();
CYLVIONPP_EXPORT std::unique_ptr<Card> Elemental(unsigned strength, unsigned enhancedStrength);
CYLVIONPP_EXPORT std::unique_ptr<Card> Blaze();
CYLVIONPP_EXPORT std::unique_ptr<Card> Simoon();

} // namespace card

} // namespace cylvionpp

#endif // CYLVIONPP_CARD_H
