#include "cylvan.h"

#include "cylvionpp/content.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {

CylvanCard::CylvanCard(unsigned cost):
    _cost(cost)
{/* Empty. */}

unsigned
CylvanCard::GetCost() const
{
    return _cost;
}

unsigned
CylvanCard::GetPriority() const
{
    throw std::logic_error("cylvan has no priority");
}

bool
CylvanCard::IsCylvan() const
{
    return true;
}

bool
CylvanCard::IsRavage() const
{
    return false;
}

bool
CylvanCard::IsBlazing() const
{
    return false;
}

void
CylvanCard::SetBlaze()
{/* Empty. */}

bool
CylvanCard::OnUse(Dealer & dealer, const Actor & actor, Index idx) const
{
    const auto & content = dealer.GetContent();
    if (content.GetMana() < GetCost()) {
        return false;
    }
    if (!OnUseEffect(dealer, actor, idx)) {
        return false;
    }
    dealer.Perform(*operation::DecreaseMana(GetCost()));
    return true;
}

bool
CylvanCard::OnUseWhenReveal(Dealer & dealer, const Actor & actor, Index idx) const
{
    if (!CanUseWhenReveal()) {
        return false;
    }
    return OnUse(dealer, actor, idx);
}

bool
CylvanCard::OnUseWhenDefend(Dealer & dealer, const Actor & actor, Index idx) const
{
    if (!CanUseWhenDefend()) {
        return false;
    }
    return OnUse(dealer, actor, idx);
}

} // namespace cylvionpp
