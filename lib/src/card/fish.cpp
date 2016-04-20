#include "defense_animal.h"

#include "cylvionpp/dealer.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {
namespace card {

namespace {

class FishCard: public DefenseAnimalCard {
public:
    FishCard();

    std::string GetName() const override;

private:
    bool OnUseEffect(Dealer & dealer, const Actor &, Index) const override;
};

FishCard::FishCard():
    DefenseAnimalCard(1)
{/* Empty. */}

std::string
FishCard::GetName() const
{
    return "fish";
}

bool
FishCard::OnUseEffect(Dealer & dealer, const Actor &, Index) const
{
    dealer.Perform(*operation::IncreaseMana(3));
    return true;
}

} // namespace

std::unique_ptr<Card>
Fish()
{
    return std::make_unique<FishCard>();
}

} // namespace card
} // namespace cylvionpp
