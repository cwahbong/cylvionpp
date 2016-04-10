#ifndef CYLVIONPP_STACK_H
#define CYLVIONPP_STACK_H

#include "cylvionpp_export.h"

namespace cylvionpp {

class CYLVIONPP_EXPORT Stack {
public:
    virtual ~Stack() = 0;

    virtual bool Empty() const = 0;
    virtual unsigned Size() const = 0;

    virtual const std::unique_ptr<Card> & Peek() const = 0;
    virtual const std::unique_ptr<Card> & Peek(Index idx) const = 0;
    virtual void Push(std::unique_ptr<Card> &&) = 0;
    virtual std::unique_ptr<Card> Pop() = 0;
    virtual void Shuffle() = 0;

    static std::unique_ptr<Stack> New();
};

CYLVIONPP_EXPORT bool operator==(const Stack &, const Stack &);
CYLVIONPP_EXPORT bool operator!=(const Stack &, const Stack &);

} // namespace cylvionpp

#endif // CYLVIONPP_STACK_H
