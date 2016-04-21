#include "on_field_cylvan.h"

#include "cylvionpp/actor.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {

OnFieldCylvanCard::OnFieldCylvanCard(unsigned cost):
    CylvanCard(cost)
{/* Empty. */}

bool
OnFieldCylvanCard::CanUseWhenReveal() const
{
    return false;
}

bool
OnFieldCylvanCard::CanUseWhenDefend() const
{
    return true;
}

bool
OnFieldCylvanCard::OnUseEffect(Dealer & dealer, const Actor & actor, Index idx) const
{
    auto row = actor.AnswerIndex("put field row", dealer.GetContent());
    auto col = actor.AnswerIndex("put field col", dealer.GetContent());
    // TODO check before put
    return dealer.Perform(*operation::PutCylvan(idx, {row, col}));
}

} // namespace cylvionpp
