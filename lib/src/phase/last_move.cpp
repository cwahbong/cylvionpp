#include "cylvionpp/phase.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/dealer_helper.h"
#include "cylvionpp/field.h"

namespace cylvionpp {
namespace phase {

namespace {

bool
FieldHasRavage(const Field & field)
{
    for (Index r = 0; r < Field::row; ++r) {
        for (Index c = 0; c < Field::col; ++c) {
            const auto & card = field.Peek({r, c});
            if (card.IsRavage()) {
                return true;
            }
        }
    }
    return false;
}

class LastMovePhase: public Phase {
public:
    std::unique_ptr<Phase> Action(Dealer & dealer, const Actor &) override;
};

std::unique_ptr<Phase>
LastMovePhase::Action(Dealer & dealer, const Actor &)
{
    while (FieldHasRavage(dealer.GetContent().GetField())) {
        if (!MoveLeftAllElementals(dealer)) {
            return nullptr;
        }
    }
    return nullptr;
}

} // namespace

std::unique_ptr<Phase>
LastMove()
{
    return std::make_unique<LastMovePhase>();
}

} // namespace phase
} // namespace cylvionpp
