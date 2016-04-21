#include "defense_animal.h"

#include "cylvionpp/dealer.h"
#include "cylvionpp/field.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {
namespace card {

namespace {

class DovesCard: public DefenseAnimalCard {
public:
    DovesCard();

    std::string GetName() const override;

private:
    bool OnUseEffect(Dealer & dealer, const Actor &, Index) const override;
};

DovesCard::DovesCard():
    DefenseAnimalCard(1)
{/* Empty. */}

std::string
DovesCard::GetName() const
{
    return "doves";
}

bool
DovesCard::OnUseEffect(Dealer & dealer, const Actor &, Index) const
{
    for (Index row = 0; row < Field::row; ++row) {
        if (!dealer.Perform(*operation::RemoveRavage(row))) {
            return false;
        }
    }
    return true;
}

} // namespace

std::unique_ptr<Card>
Doves()
{
    return std::make_unique<DovesCard>();
}

} // namespace card
} // namespace cylvionpp
