#include "cylvionpp/card.h"

#include <exception>

#include "cylvionpp/actor.h"

namespace cylvionpp {
namespace core {

Card::~Card()
{/* Empty. */}

bool
Card::OnBeforeMove(std::unique_ptr<Card> && card, Dealer & dealer, const Actor & actor)
{
    return card->OnBeforeMove(dealer, actor, std::move(card));
}

bool
Card::OnUseWhenReveal(std::unique_ptr<Card> && card, Dealer & dealer, const Actor & actor)
{
    return card->OnUseWhenReveal(dealer, actor, std::move(card));
}

bool
Card::OnUseWhenDefend(std::unique_ptr<Card> && card, Dealer & dealer, const Actor & actor)
{
    return card->OnUseWhenDefend(dealer, actor, std::move(card));
}

} // namespace core
} // namespace cylvionpp
