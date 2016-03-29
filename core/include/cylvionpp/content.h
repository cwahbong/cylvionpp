#ifndef CYLVIONPP_CONTENT_H
#define CYLVIONPP_CONTENT_H

#include <memory>

namespace cylvionpp {
namespace core {

class CardFactory;
class Field;
class Hand;
class Stack;

class Content {
public:
    virtual ~Content() = 0;

    virtual unsigned GetEdge() const = 0;
    virtual void IncreaseEdge(unsigned) = 0;
    virtual void DecreaseEdge(unsigned) = 0;
    virtual void SetEdge(unsigned) = 0;

    virtual unsigned GetMana() const = 0;
    virtual void SetMana(unsigned) = 0;

    virtual const Field & GetField() const = 0;
    virtual Field & GetField() = 0;

    virtual const Hand & GetHand() const = 0;
    virtual Hand & GetHand() = 0;

    virtual const Stack & GetDiscarded() const = 0;
    virtual Stack & GetDiscarded() = 0;

    virtual const Stack & GetUndrawn() const = 0;
    virtual Stack & GetUndrawn() = 0;

    static std::unique_ptr<Content> New();
};

} // namespace core
} // namespace cylvionpp

#endif // CYLVIONPP_CONTENT_H
