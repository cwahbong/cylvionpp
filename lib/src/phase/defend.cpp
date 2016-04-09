#include "cylvionpp/phase.h"

#include "cylvionpp/content.h"
#include "cylvionpp/content_helper.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/dealer_helper.h"
#include "cylvionpp/field.h"
#include "cylvionpp/hand.h"
#include "cylvionpp/operation.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {
namespace phase {

namespace {

bool
RavageStackHasRavage(const Content & content)
{
    return content.GetField().GetRavageStack(0).Empty();
}

class DefendPhase: public Phase {
public:
    std::unique_ptr<Phase> Action(Dealer & dealer, const Actor & actor) override;
};

std::unique_ptr<Phase>
DefendPhase::Action(Dealer & dealer, const Actor & actor)
{
    if (!ActDefendActions(dealer, actor)) {
        return nullptr;
    }
    const auto & hand = dealer.GetContent().GetHand();
    while (hand.Size() > 10) {
        if (!DiscardChooseFromHand(dealer, actor)) {
            return nullptr;
        }
    }
    if (!RavageStackHasRavage(dealer.GetContent())) {
        return LastMove();
    }
    return Reveal();
}

} // namespace

std::unique_ptr<Phase>
Defend()
{
    return std::make_unique<DefendPhase>();
}

} // namespace phase
} // namespace cylvionpp
