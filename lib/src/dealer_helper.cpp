#include "cylvionpp/dealer_helper.h"

#include "cylvionpp/actor.h"
#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/field.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {

bool
MoveLeftAllElementals(Dealer & dealer)
{
    const auto & field = dealer.GetContent().GetField();
    for (Index row = 0; row < Field::row; ++row) {
        for (Index col = 0; col < Field::col; ++col) {
            const auto & card = field.Peek({row, col});
            if (!card.IsRavage()) {
                continue;
            }
            if (col == 0) {
                if (!dealer.Perform(*operation::MoveOutElemental({row, col}))) {
                    return false;
                }
            } else {
                if (!dealer.Perform(*operation::MoveElemental({row, col}, {row, col - 1}))) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool
DiscardChooseFromHand(Dealer & dealer, const Actor & actor)
{
    auto idx = actor.AnswerIndex("discard hand");
    return dealer.Perform(*operation::PlayerDiscardHand(idx));
}

bool
ResolveSupport(Dealer & dealer, const Actor & actor, const Location & location)
{
    const auto & card = dealer.GetContent().GetField().Peek(location);
    return card.OnBeforeMove(dealer, actor, location);
}

} // namespace cylvionpp
