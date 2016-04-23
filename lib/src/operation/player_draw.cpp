#include "cylvionpp/operation.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/hand.h"
#include "cylvionpp/stack.h"

#include <sstream>

namespace cylvionpp {
namespace operation {

namespace {

class PlayerDrawOperation: public Operation {
public:
    PlayerDrawOperation(size_t count);

    std::string GetName() const override;
    std::string GetDescription() const override;

    bool Run(Content &) override;

private:
    size_t _count;
};

PlayerDrawOperation::PlayerDrawOperation(size_t count):
    _count(count)
{/* Empty. */}

std::string
PlayerDrawOperation::GetName() const
{
    return "player draw";
}

std::string
PlayerDrawOperation::GetDescription() const
{
    std::ostringstream oss;
    if (_count == 1) {
        oss << _count << " card is drawn by player";
    } else {
        oss << _count << " cards are drawn by player";
    }
    return oss.str();
}

bool
PlayerDrawOperation::Run(Content & content)
{
    for (decltype(_count) i = 0; i < _count; ++i) {
        auto & undrawn = content.GetUndrawn();
        if (undrawn.Empty()) {
            auto & discarded = content.GetDiscarded();
            while (discarded.Size()) {
                undrawn.Push(discarded.Remove(0));
            }
            undrawn.Shuffle();
        }
        content.GetHand().Add(undrawn.Pop());
    }
    return true;
}

} // namespace

std::unique_ptr<Operation>
PlayerDraw(size_t count)
{
    return std::make_unique<PlayerDrawOperation>(count);
}

} // namespace operation
} // namespace cylvionpp
