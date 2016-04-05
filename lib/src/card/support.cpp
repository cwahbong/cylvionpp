#include "support.h"

#include "cylvionpp/dealer.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {

unsigned
SupportCard::GetStrength() const
{
    throw std::logic_error("Support has no strength");
}

bool
SupportCard::IsBlazing() const
{
    return false;
}

void
SupportCard::SetBlaze()
{/* Empty. */}

bool
SupportCard::OnBeforeMove(Dealer & dealer, const Actor & actor, const Location & location) const
{
    if (!OnBeforeMoveEffect(dealer, actor, location)) {
        return false;
    }
    return dealer.Perform(*operation::RemoveFromField(location));
}

} // namespace cylvionpp
