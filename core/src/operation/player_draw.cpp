#include "cylvionpp/operation.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/hand.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {
namespace core {
namespace operation {

namespace {

class PlayerDrawOperation: public Operation {
public:
    PlayerDrawOperation(size_t count);

    std::string GetName() const override {return ""; }
    std::string GetDescription() const override { return ""; }

    bool Run(Content &) override;

private:
    size_t _count;
};

PlayerDrawOperation::PlayerDrawOperation(size_t count):
    _count(count)
{/* Empty. */}

bool
PlayerDrawOperation::Run(Content & content)
{
    for (decltype(_count) i = 0; i < _count; ++i) {
        auto & undrawn = content.GetUndrawn();
        if (undrawn.Empty()) {
            auto & discarded = content.GetDiscarded();
            while (!discarded.Empty()) {
                undrawn.Push(discarded.Pop());
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
} // namespace core
} // namespace cylvionpp
