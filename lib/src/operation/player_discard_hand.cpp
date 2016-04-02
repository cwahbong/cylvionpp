#include "cylvionpp/operation.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/hand.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {
namespace operation {

namespace {

class PlayerDiscardHandOperation: public Operation {
public:
    PlayerDiscardHandOperation(size_t idx);

    std::string GetName() const override {return ""; }
    std::string GetDescription() const override { return ""; }

    bool Run(Content &) override;

private:
    size_t _idx;
};

PlayerDiscardHandOperation::PlayerDiscardHandOperation(size_t idx):
    _idx(idx)
{/* Empty. */}

bool
PlayerDiscardHandOperation::Run(Content & content)
{
    auto & hand = content.GetHand();
    try {
        content.GetDiscarded().Push(hand.Remove(_idx));
    } catch (const std::out_of_range &) {
        return false;
    }
    return true;
}

} // namespace operation

std::unique_ptr<Operation>
PlayerDiscardHand(size_t idx)
{
    return std::make_unique<PlayerDiscardHandOperation>(idx);
}

} // namespace operation
} // namespace cylvionpp
