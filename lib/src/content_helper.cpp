#include "cylvionpp/content_helper.h"

#include <functional>
#include <sstream>

#include "cylvionpp/actor.h"
#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/field.h"
#include "cylvionpp/hand.h"
#include "cylvionpp/operation.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {

void
StartingShuffle(Content & content)
{
    content.GetUndrawn().Shuffle();
    for (size_t i = 0; i < Field::row; ++i) {
        content.GetField().GetRavageStack(i).Shuffle();
    }
}

namespace {

bool
ActActions(Dealer & dealer, std::function<Action ()> getAction, std::function<bool (Index)> cardOnUse)
{
    while (true) {
        Action action = getAction();
        if (action.end) {
            break;
        }
        Index idx;
        std::stringstream ss(action.additional["idx"]);
        ss >> idx;
        // TODO handle out or range
        if (action.additional["type"] == "discard") {
            if (!dealer.Perform(*operation::PlayerDiscardHand(idx))) {
                return false;
            }
        } else if (action.additional["type"] == "use") {
            if (!cardOnUse(idx)) {
                return false;
            }
        }
    }
    return true;
}

} // namespace

bool
ActRevealActions(Dealer & dealer, const Actor & actor)
{
    auto getAction = [&actor, &dealer]() {
        return actor.RevealAction(dealer.GetContent());
    };
    auto cardOnUse = [&actor, &dealer](Index idx) {
        const auto & card = dealer.GetContent().GetHand().Peek(idx);
        return card->OnUseWhenReveal(dealer, actor, idx);
    };
    return ActActions(dealer, getAction, cardOnUse);
}

bool
ActDefendActions(Dealer & dealer, const Actor & actor)
{
    auto getAction = [&actor, &dealer]() {
        return actor.DefendAction(dealer.GetContent());
    };
    auto cardOnUse = [&actor, &dealer](Index idx) {
        const auto & card = dealer.GetContent().GetHand().Peek(idx);
        return card->OnUseWhenDefend(dealer, actor, idx);
    };
    return ActActions(dealer, getAction, cardOnUse);
}

} // namespace cylvionpp
