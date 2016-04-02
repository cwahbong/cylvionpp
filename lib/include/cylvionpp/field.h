#ifndef CYLVIONPP_FIELD_H
#define CYLVIONPP_FIELD_H

#include "cylvionpp_export.h"

#include <memory>

namespace cylvionpp {

class Card;
class Stack;

class CYLVIONPP_EXPORT Field {
public:
    virtual ~Field() = 0;

    virtual bool Empty() const = 0;

    virtual const Card & Peek(size_t row, size_t col) const = 0;
    virtual Card & Peek(size_t row, size_t col) = 0;
    virtual bool Put(size_t row, size_t col, std::unique_ptr<Card> &&) = 0;
    virtual bool Move(size_t row, size_t col, size_t to_row, size_t toCol) = 0;
    virtual std::unique_ptr<Card> Remove(size_t row, size_t col) = 0;

    virtual const Stack & GetRavageStack(size_t row) const = 0;
    virtual Stack & GetRavageStack(size_t row) = 0;

    const static size_t row = 4;
    const static size_t col = 5;
    static std::unique_ptr<Field> New();

};

void CYLVIONPP_EXPORT MoveElemental(Field & field, size_t fromRow, size_t fromCol, size_t toRow, size_t toCol);

} // namespace cylvionpp

#endif // CYLVIONPP_FIELD_H
