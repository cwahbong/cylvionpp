#include "cylvionpp/phase.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/content_helper.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/dealer_helper.h"
#include "cylvionpp/field.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {
namespace phase {

namespace {

class RevealPhase: public Phase {
public:
    std::unique_ptr<Phase> Action(Dealer & dealer, const Actor & actor) override;

private:
    bool ResolveSupports(Dealer & dealer, const Actor & actor, unsigned order);
};

bool
RevealPhase::ResolveSupports(Dealer & dealer, const Actor & actor, unsigned order)
{
    const auto & field = dealer.GetContent().GetField();
    const auto col = Field::col - 1;
    for (Index row = 0; row < Field::row; ++row) {
        const auto & peeked = field.Peek({row, col});
        if (peeked.IsNone() || peeked.GetPriority() != order) {
            continue;
        }
        if (!ResolveSupport(dealer, actor, {row, col})) {
            return false;
        }
    }
    return true;
}

std::unique_ptr<Phase>
RevealPhase::Action(Dealer & dealer, const Actor & actor)
{
    for (Index row = 0; row < Field::row; ++row) {
        if (!dealer.Perform(*operation::RevealRavage(row))) {
            return nullptr;
        }
    }
    if (!ActRevealActions(dealer, actor)) {
        return nullptr;
    }
    for (unsigned i = 0; i < 4; ++i) {
        if (!ResolveSupports(dealer, actor, i)) {
            return nullptr;
        }
    }
    return Move();
}

} // namespace

std::unique_ptr<Phase>
Reveal()
{
    return std::make_unique<RevealPhase>();
}

} // namespace phase
} // namespace cylvionpp
