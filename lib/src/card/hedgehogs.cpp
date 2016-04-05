#include "animal.h"

#include "cylvionpp/actor.h"
#include "cylvionpp/content.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/field.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {
namespace card {

namespace {

class HedgehogsCard: public AnimalCard {
public:
    HedgehogsCard();

private:
    bool CanUseWhenReveal() const;
    bool CanUseWhenDefend() const;
    bool OnUseEffect(Dealer & dealer, const Actor & actor, Index) const override;
};

HedgehogsCard::HedgehogsCard():
    AnimalCard(0)
{/* Empty. */}

bool
HedgehogsCard::CanUseWhenReveal() const
{
    return true;
}

bool
HedgehogsCard::CanUseWhenDefend() const
{
    return false;
}

bool
HedgehogsCard::OnUseEffect(Dealer & dealer, const Actor & actor, Index) const
{
    const auto row = actor.AnswerIndex("elem row");
    const auto col = Field::col - 1;
    const auto & field = dealer.GetContent().GetField();
    if (!field.Peek({row, col}).IsRavage()) {
        return false;
    }
    return dealer.Perform(*operation::RemoveFromField({row, col}));
}

} // namespace

std::unique_ptr<Card>
Hedgehogs()
{
    return std::make_unique<HedgehogsCard>();
}

} // namespace card
} // namespace cylvionpp
