#ifndef CYLVION_DEALER_H
#define CYLVION_DEALER_H

#include <memory>

namespace cylvionpp {
namespace core {

class Content;
class Operation;
class OperationFactory;

class Dealer {
public:
    virtual ~Dealer() = 0;

    virtual const Content & GetContent() const = 0;

    // TODO add observer for dealer
    virtual bool Perform(Operation &) = 0;

    static std::unique_ptr<Dealer> New(std::unique_ptr<Content> content);
};

bool MoveLeftAllElementals(Dealer &);

} // namespace core
} // namespace cylvionpp

#endif // CYLVION_DEALER_H
