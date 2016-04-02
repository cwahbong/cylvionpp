#ifndef CYLVIONPP_CARD_H
#define CYLVIONPP_CARD_H

#include <memory>

namespace cylvionpp {
namespace core {

class Actor;
class Dealer;

class Card {
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

    virtual bool OnBeforeMove(Dealer & dealer, const Actor & actor) const = 0;

    static bool OnUseWhenReveal(std::unique_ptr<Card> && card, Dealer & dealer, const Actor & actor);
    static bool OnUseWhenDefend(std::unique_ptr<Card> && card, Dealer & dealer, const Actor & actor);

private:
    virtual bool OnUseWhenReveal(Dealer & dealer, const Actor & actor, std::unique_ptr<Card> && self) = 0;
    virtual bool OnUseWhenDefend(Dealer & dealer, const Actor & actor, std::unique_ptr<Card> && self) = 0;
};

} // namespace core
} // namespace cylvionpp

#endif // CYLVIONPP_CARD_H
