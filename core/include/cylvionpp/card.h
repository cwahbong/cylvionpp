#ifndef CYLVIONPP_CARD_H
#define CYLVIONPP_CARD_H

#include <memory>

namespace cylvionpp {
namespace core {

class Content;
class Actor;

class Card {
public:
    virtual ~Card() = 0;

    virtual unsigned GetCost() const = 0;
    virtual unsigned GetStrength() const = 0;
    virtual unsigned GetVitality() const = 0;

    virtual bool IsCylvan() const = 0;
    virtual bool IsRavage() const = 0;
    virtual bool IsNone() const = 0;

    static bool OnBeforeMove(std::unique_ptr<Card> && card, Content & content, const Actor & actor);
    static bool OnUseWhenReveal(std::unique_ptr<Card> && card, Content & content, const Actor & actor);
    static bool OnUseWhenDefend(std::unique_ptr<Card> && card, Content & content, const Actor & actor);

    static std::unique_ptr<Card> NewNone();
    static std::unique_ptr<Card> NewFountain(unsigned cost, unsigned strength);
    static std::unique_ptr<Card> NewTree(unsigned cost, unsigned vitality);
    // static std::unique_ptr<Card> NewAnimal(unsigned cost, ...);
    static std::unique_ptr<Card> NewElemental(unsigned strength, unsigned enhancedStrength);
    // static std::unique_ptr<Card> NewSupport(...);

private:
    virtual bool OnBeforeMove(Content & content, const Actor & actor, std::unique_ptr<Card> && self) = 0;
    virtual bool OnUseWhenReveal(Content & content, const Actor & actor, std::unique_ptr<Card> && self) = 0;
    virtual bool OnUseWhenDefend(Content & content, const Actor & actor, std::unique_ptr<Card> && self) = 0;
};

} // namespace core
} // namespace cylvionpp

#endif // CYLVIONPP_CARD_H
