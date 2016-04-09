#ifndef CYLVIONPP_HAND_H
#define CYLVIONPP_HAND_H

#include "cylvionpp_export.h"
#include "types.h"

#include <cstdlib>
#include <memory>

namespace cylvionpp {

class Card;

class CYLVIONPP_EXPORT Hand {
public:
    virtual ~Hand() = 0;

    virtual size_t Size() const = 0;

    virtual const Card & Peek(Index idx) const = 0;
    virtual void Add(std::unique_ptr<Card> && card) = 0;
    virtual std::unique_ptr<Card> Remove(Index idx) = 0;

    static std::unique_ptr<Hand> New();
};

} // namespace cylvionpp

#endif // CYLVIONPP_HAND_H
