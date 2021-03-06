#ifndef CYLVION_DEALER_H
#define CYLVION_DEALER_H

#include "cylvionpp_export.h"

#include <memory>

namespace cylvionpp {

class Content;
class Observer;
class Operation;

class CYLVIONPP_EXPORT Dealer {
public:
    virtual ~Dealer() = 0;

    virtual const Content & GetContent() const = 0;

    virtual bool Perform(Operation &) = 0;

    static std::unique_ptr<Dealer> New(std::unique_ptr<Content> content, std::shared_ptr<Observer> observer);
};

} // namespace cylvionpp

#endif // CYLVION_DEALER_H
