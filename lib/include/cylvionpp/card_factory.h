#ifndef CYLVIONPP_CARD_FACTORY_H
#define CYLVIONPP_CARD_FACTORY_H

#include <memory>

namespace cylvionpp {

class Card;

class CardFactory {
public:
    virtual std::unique_ptr<Card> NewNone() = 0;
    virtual std::unique_ptr<Card> NewFountain(unsigned cost, unsigned strength) = 0;
    virtual std::unique_ptr<Card> NewTree(unsigned cost, unsigned vitality) = 0;
    virtual std::unique_ptr<Card> NewWhale() = 0;
    virtual std::unique_ptr<Card> NewElephant() = 0;
    virtual std::unique_ptr<Card> NewHedgehogs() = 0;
    virtual std::unique_ptr<Card> NewOwl() = 0;
    virtual std::unique_ptr<Card> NewElemental(unsigned strength, unsigned enhancedStrength) = 0;
    virtual std::unique_ptr<Card> NewBlaze() = 0;
    virtual std::unique_ptr<Card> NewSimoon() = 0;
};

std::unique_ptr<CardFactory> NewCardFactory();

} // namespace cylvionpp

#endif // CYLVIONPP_CARD_FACTORY_H
