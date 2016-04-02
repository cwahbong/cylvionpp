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
    for (size_t row = 0; row < Field::row; ++row) {
        for (size_t col = 0; col < Field::col; ++col) {
            const auto & card = field.Peek(row, col);
            if (!card.IsRavage()) {
                continue;
            }
            if (col == 0) {
                dealer.Perform(*operation::MoveOutElemental(row, col));
            } else {
                dealer.Perform(*operation::MoveElemental(row, col, row, col - 1));
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
ResolveSupport(Dealer & dealer, const Actor & actor, size_t row, size_t col)
{
    const auto & card = dealer.GetContent().GetField().Peek(row, col);
    return card.OnBeforeMove(dealer, actor, row, col);
}

} // namespace cylvionpp
