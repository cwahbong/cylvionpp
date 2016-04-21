#include "defense_animal.h"

#include "cylvionpp/actor.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/field.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {
namespace card {

namespace {

class SquirrelsCard: public DefenseAnimalCard {
public:
    SquirrelsCard();

    std::string GetName() const override;

private:
    bool OnUseEffect(Dealer & dealer, const Actor &, Index) const override;
};

SquirrelsCard::SquirrelsCard():
    DefenseAnimalCard(1)
{/* Empty. */}

std::string
SquirrelsCard::GetName() const
{
    return "squirrels";
}

bool
SquirrelsCard::OnUseEffect(Dealer & dealer, const Actor & actor, Index) const
{
    for (Index row = 0; row < Field::row; ++row) {
        const auto reverse = actor.AnswerIndex("squirrels reverse");
        if (reverse) {
            dealer.Perform(*operation::ReverseTop2Ravage(reverse));
        }
    }
    return true;
}

} // namespace

std::unique_ptr<Card>
Squirrels()
{
    return std::make_unique<SquirrelsCard>();
}

} // namespace card
} // namespace cylvionpp
