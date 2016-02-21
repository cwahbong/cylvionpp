#ifndef CYLVIONPP_HAND_H
#define CYLVIONPP_HAND_H

#include <cstdlib>
#include <memory>

namespace cylvionpp {
namespace core {

class Card;

class Hand {
public:
    virtual size_t Size() const = 0;

    virtual const std::unique_ptr<Card> & Peek(size_t idx) const = 0;
    virtual void Add(std::unique_ptr<Card> && card) = 0;
    virtual std::unique_ptr<Card> Remove(size_t idx) = 0;

    static std::unique_ptr<Hand> New();
};

} // namespace core
} // namespace cylvionpp

#endif // CYLVIONPP_HAND_H
