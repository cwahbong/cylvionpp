#include "support.h"

#include "cylvionpp/dealer_helper.h"

namespace cylvionpp {
namespace card {

namespace {

class SimoonCard: public SupportCard {
    std::string GetName() const override;
    unsigned GetPriority() const override;

    bool OnBeforeMoveEffect(Dealer &, const Actor &, const Location &) const override;
};

std::string
SimoonCard::GetName() const
{
    return "simoon";
}

unsigned
SimoonCard::GetPriority() const
{
    return 3;
}

bool
SimoonCard::OnBeforeMoveEffect(Dealer & dealer, const Actor &, const Location &) const
{
    MoveLeftAllElementals(dealer);
    return true;
}

} // namespace

std::unique_ptr<Card>
Simoon()
{
    return std::make_unique<SimoonCard>();
}

} // namespace card
} // namespace cylvionpp
