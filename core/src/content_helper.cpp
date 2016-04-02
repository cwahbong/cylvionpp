#include "cylvionpp/content_helper.h"

#include <functional>
#include <sstream>

#include "cylvionpp/actor.h"
#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/field.h"
#include "cylvionpp/hand.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {
namespace core {

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
ActActions(const Content & content, std::function<Action ()> getAction, std::function<bool (std::unique_ptr<Card> &&)> cardOnUse)
{
    const auto & hand = content.GetHand();
    const auto & discarded = content.GetDiscarded();
    while (true) {
        Action action = getAction();
        if (action.end) {
            break;
        }
        size_t idx;
        std::stringstream ss(action.additional["idx"]);
        ss >> idx;
        // TODO handle out or range
        /* std::unique_ptr<Card> card = hand.Remove(idx);
        if (action.additional["type"] == "discard") {
            discarded.Push(std::move(card));
            content.SetMana(content.GetMana() + 1); // XXX
        } else if (action.additional["type"] == "use") {
            if (!cardOnUse(std::move(card))) {
                return false;
            }
        }
        if (card) {
            hand.Add(std::move(card));
        } */
    }
    return true;
}

} // namespace

bool
ActRevealActions(Dealer & dealer, const Content & content, const Actor & actor)
{
    auto getAction = [&actor, &content]() {
        return actor.RevealAction(content);
    };
    auto cardOnUse = [&actor, &dealer](std::unique_ptr<Card> && card) {
        return Card::OnUseWhenReveal(std::move(card), dealer, actor);
    };
    // return ActActions(content, getAction, cardOnUse);
}

bool
ActDefendActions(Dealer & dealer, const Content & content, const Actor & actor)
{
    auto getAction = [&actor, &content]() {
        return actor.DefendAction(content);
    };
    auto cardOnUse = [&actor, &content](std::unique_ptr<Card> && card) {
        // return Card::OnUseWhenDefend(std::move(card), content, actor);
    };
    // return ActActions(content, getAction, cardOnUse);
}

} // namespace core
} // namespace cylvionpp
