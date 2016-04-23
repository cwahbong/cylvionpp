#include "support.h"

#include "cylvionpp/actor.h"
#include "cylvionpp/content_helper.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {
namespace card {

namespace {

class DemobilizationCard: public SupportCard {
    std::string GetName() const override;
    unsigned GetPriority() const override;

    bool OnBeforeMoveEffect(Dealer &, const Actor &, const Location &) const override;
};

std::string
DemobilizationCard::GetName() const
{
    return "demobilization";
}

unsigned
DemobilizationCard::GetPriority() const
{
    return 1;
}

bool
DemobilizationCard::OnBeforeMoveEffect(Dealer & dealer, const Actor & actor, const Location &) const
{
    const auto assign = actor.AnswerIndex("demobilization assign", dealer.GetContent());
    if (assign) {
        for (unsigned i = 0; i < 2; ++i) {
            const auto removeIndex = actor.AnswerIndex("demobilization discard", dealer.GetContent());
            dealer.Perform(*operation::RemoveFromDiscarded(removeIndex));
        }
    } else {
        const auto removeIndex = RandomDiscardedIndex(dealer.GetContent());
        dealer.Perform(*operation::RemoveFromDiscarded(removeIndex));
    }
    return true;
}

} // namespace

std::unique_ptr<Card>
Demobilization()
{
    return std::make_unique<DemobilizationCard>();
}

} // namespace card
} // namesapce cylvionpp
