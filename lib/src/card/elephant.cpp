#include "defense_animal.h"

#include "cylvionpp/actor.h"
#include "cylvionpp/content.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/field.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {
namespace card {

namespace {

class ElephantCard: public DefenseAnimalCard {
public:
    ElephantCard();

    std::string GetName() const override;

private:
    bool OnUseEffect(Dealer & dealer, const Actor & actor, Index) const override;
};

ElephantCard::ElephantCard():
    DefenseAnimalCard(1)
{/* Empty. */}

std::string
ElephantCard::GetName() const
{
    return "elephant";
}

bool
ElephantCard::OnUseEffect(Dealer & dealer, const Actor & actor, Index) const
{
    const auto row = actor.AnswerIndex("elem row");
    const auto col = actor.AnswerIndex("elem col");
    const auto & field = dealer.GetContent().GetField();
    if (!field.Peek({row, col}).IsNone()) {
        return false;
    }
    return dealer.Perform(*operation::RemoveFromField({row, col}));
}

} // namespace

std::unique_ptr<Card>
Elephant()
{
    return std::make_unique<ElephantCard>();
}

} // namespace card
} // namespace cylvionpp
