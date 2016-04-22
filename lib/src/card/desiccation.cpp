#include "support.h"

#include "cylvionpp/actor.h"
#include "cylvionpp/content_helper.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {
namespace card {

namespace {

class DesiccationCard: public SupportCard {
    std::string GetName() const override;
    unsigned GetPriority() const override;

    bool OnBeforeMoveEffect(Dealer &, const Actor &, const Location &) const override;
};

std::string
DesiccationCard::GetName() const
{
    return "desiccation";
}

unsigned
DesiccationCard::GetPriority() const
{
    return 0;
}

bool
DesiccationCard::OnBeforeMoveEffect(Dealer & dealer, const Actor & actor, const Location &) const
{
    const auto assign = actor.AnswerIndex("desiccation assign", dealer.GetContent());
    if (assign) {
        for (unsigned i = 0; i < 2; ++i) {
            const auto discardIndex = actor.AnswerIndex("desiccation discard", dealer.GetContent());
            dealer.Perform(*operation::PlayerDiscardHand(discardIndex));
        }
    } else {
        const auto discardIndex = RandomHandIndex(dealer.GetContent());
        dealer.Perform(*operation::PlayerDiscardHand(discardIndex));
    }
    return true;
}

} // namespace

std::unique_ptr<Card>
Desiccation()
{
    return std::make_unique<DesiccationCard>();
}

} // namespace card
} // namesapce cylvionpp
