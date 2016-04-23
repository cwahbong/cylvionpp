#ifndef CYLVIONPP_CONTENT_H
#define CYLVIONPP_CONTENT_H

#include "cylvionpp_export.h"
#include "types.h"

#include <memory>

namespace cylvionpp {

class CardFactory;
class Desertions;
class Field;
class Hand;
class Stack;

class CYLVIONPP_EXPORT Content {
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

    virtual const Stack & GetRecuitment(Index col) const = 0;
    virtual Stack & GetRecuitment(Index col) = 0;

    virtual const Stack & GetSylvan() const = 0;
    virtual Stack & GetSylvan() = 0;

    virtual const Desertions & GetDesertions() const = 0;
    virtual Desertions & GetDesertions() = 0;

    virtual const Hand & GetDiscarded() const = 0;
    virtual Hand & GetDiscarded() = 0;

    virtual const Stack & GetUndrawn() const = 0;
    virtual Stack & GetUndrawn() = 0;

    static std::unique_ptr<Content> New();
};

CYLVIONPP_EXPORT bool operator==(const Content &, const Content &);
CYLVIONPP_EXPORT bool operator!=(const Content &, const Content &);

} // namespace cylvionpp

#endif // CYLVIONPP_CONTENT_H
