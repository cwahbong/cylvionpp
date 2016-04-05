#include "support.h"

#include "cylvionpp/dealer_helper.h"

namespace cylvionpp {
namespace card {

namespace {

class SimoonCard: public SupportCard {
    unsigned GetPriority() const override;

    bool OnBeforeMoveEffect(Dealer &, const Actor &, const Location &) const override;
};

unsigned
SimoonCard::GetPriority() const
{
    return 3;
}

bool
SimoonCard::OnBeforeMoveEffect(Dealer & dealer, const Actor &, const Location &) const
{
    MoveLeftAllElementals(dealer);
    return false;
}

} // namespace

std::unique_ptr<Card>
Simoon()
{
    return std::make_unique<SimoonCard>();
}

} // namespace card
} // namespace cylvionpp
