#ifndef CYLVIONPP_FIELD_H
#define CYLVIONPP_FIELD_H

#include <memory>

namespace cylvionpp {
namespace core {

class Card;
class Stack;

class Field {
public:
    virtual ~Field() = 0;

    virtual bool Empty() const = 0;

    virtual const std::unique_ptr<Card> & Peek(size_t row, size_t col) const = 0;
    virtual bool Put(size_t row, size_t col, std::unique_ptr<Card> &&) = 0;
    virtual bool Move(size_t row, size_t col, size_t to_row, size_t toCol) = 0;
    virtual std::unique_ptr<Card> Remove(size_t row, size_t col) = 0;

    virtual const Stack & GetRavageStack(size_t row) const = 0;
    virtual Stack & GetRavageStack(size_t row) = 0;

    const static size_t row = 4;
    const static size_t col = 5;
    static std::unique_ptr<Field> New();
};

} // namespace core
} // namespace cylvionpp

#endif // CYLVIONPP_FIELD_H
