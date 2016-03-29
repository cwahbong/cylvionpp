#include "cylvionpp/card.h"

#include <exception>

#include "cylvionpp/actor.h"
#include "cylvionpp/content.h"
#include "cylvionpp/content_helper.h"
#include "cylvionpp/field.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {
namespace core {

Card::~Card()
{/* Empty. */}

bool
Card::OnBeforeMove(std::unique_ptr<Card> && card, Content & content, const Actor & actor)
{
    return card->OnBeforeMove(content, actor, std::move(card));
}

bool
Card::OnUseWhenReveal(std::unique_ptr<Card> && card, Content & content, const Actor & actor)
{
    return card->OnUseWhenReveal(content, actor, std::move(card));
}

bool
Card::OnUseWhenDefend(std::unique_ptr<Card> && card, Content & content, const Actor & actor)
{
    return card->OnUseWhenDefend(content, actor, std::move(card));
}

} // namespace core
} // namespace cylvionpp
