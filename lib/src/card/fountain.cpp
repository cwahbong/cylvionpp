#include "on_field_cylvan.h"

namespace cylvionpp {
namespace card {
namespace {

class FountainCard: public OnFieldCylvanCard {
public:
    FountainCard(unsigned cost, unsigned strength);

    unsigned GetStrength() const override;
    unsigned GetVitality() const override;

private:
    unsigned _strength;
};

FountainCard::FountainCard(unsigned cost, unsigned strength):
    OnFieldCylvanCard(cost),
    _strength(strength)
{/* Empty. */}

unsigned
FountainCard::GetStrength() const
{
    return _strength;
}

unsigned
FountainCard::GetVitality() const
{
    return 0;
}

} // namespace

std::unique_ptr<Card>
Fountain(unsigned cost, unsigned strength)
{
    return std::make_unique<FountainCard>(cost, strength);
}

} // namespace card
} // namespace cylvionpp
