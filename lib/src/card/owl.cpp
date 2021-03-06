#include "defense_animal.h"

#include "cylvionpp/dealer.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {
namespace card {

namespace {

class OwlCard: public DefenseAnimalCard {
public:
    OwlCard();

    std::string GetName() const override;

private:
    bool OnUseEffect(Dealer & dealer, const Actor &, Index) const override;
};

OwlCard::OwlCard():
    DefenseAnimalCard(1)
{/* Empty. */}

std::string
OwlCard::GetName() const
{
    return "owl";
}

bool
OwlCard::OnUseEffect(Dealer & dealer, const Actor &, Index) const
{
    return dealer.Perform(*operation::PlayerDraw(3));
}

} // namespace

std::unique_ptr<Card>
Owl()
{
    return std::make_unique<OwlCard>();
}

} // namespace card
} // namespace cylvionpp
