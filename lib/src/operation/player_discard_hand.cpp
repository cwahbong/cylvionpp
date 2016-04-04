#include "cylvionpp/operation.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/hand.h"
#include "cylvionpp/stack.h"

#include <sstream>

namespace cylvionpp {
namespace operation {

namespace {

class PlayerDiscardHandOperation: public Operation {
public:
    PlayerDiscardHandOperation(Index idx);

    std::string GetName() const override;
    std::string GetDescription() const override;

    bool Run(Content &) override;

private:
    size_t _idx;
};

PlayerDiscardHandOperation::PlayerDiscardHandOperation(Index idx):
    _idx(idx)
{/* Empty. */}

std::string
PlayerDiscardHandOperation::GetName() const
{
    return "player discard";
}

std::string
PlayerDiscardHandOperation::GetDescription() const
{
    std::ostringstream oss;
    oss << _idx << "-th card is discarded";
    return oss.str();
}

bool
PlayerDiscardHandOperation::Run(Content & content)
{
    auto & hand = content.GetHand();
    try {
        content.GetDiscarded().Push(hand.Remove(_idx));
        content.SetMana(content.GetMana() + 1);
    } catch (const std::out_of_range &) {
        return false;
    }
    return true;
}

} // namespace operation

std::unique_ptr<Operation>
PlayerDiscardHand(Index idx)
{
    return std::make_unique<PlayerDiscardHandOperation>(idx);
}

} // namespace operation
} // namespace cylvionpp
