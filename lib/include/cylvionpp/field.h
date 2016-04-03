#ifndef CYLVIONPP_FIELD_H
#define CYLVIONPP_FIELD_H

#include "cylvionpp_export.h"
#include "types.h"

#include <memory>

namespace cylvionpp {

class Card;
class Stack;

class CYLVIONPP_EXPORT Field {
public:
    virtual ~Field() = 0;

    virtual bool Empty() const = 0;

    virtual const Card & Peek(const Location & location) const = 0;
    virtual Card & Peek(const Location & location) = 0;
    virtual bool Put(const Location & location, std::unique_ptr<Card> &&) = 0;
    virtual bool Move(const Location & from, const Location & to) = 0;
    virtual std::unique_ptr<Card> Remove(const Location & location) = 0;

    virtual const Stack & GetRavageStack(Index row) const = 0;
    virtual Stack & GetRavageStack(Index row) = 0;

    const static Index row = 4;
    const static Index col = 5;
    static std::unique_ptr<Field> New();

};

void CYLVIONPP_EXPORT MoveElemental(Field & field, const Location & from, const Location & to);

} // namespace cylvionpp

#endif // CYLVIONPP_FIELD_H
