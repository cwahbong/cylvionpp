#include "on_field_cylvan.h"

namespace cylvionpp {
namespace card {

namespace {

class TreeCard: public OnFieldCylvanCard {
public:
    TreeCard(unsigned cost, unsigned vitality);

    std::string GetName() const override;
    unsigned GetStrength() const override;
    unsigned GetVitality() const override;

private:
    unsigned _vitality;
};

TreeCard::TreeCard(unsigned cost, unsigned vitality):
    OnFieldCylvanCard(cost),
    _vitality(vitality)
{/* Empty. */}

std::string
TreeCard::GetName() const
{
    return std::string("tree ") + std::to_string(GetCost()) + " " + std::to_string(_vitality);
}

unsigned
TreeCard::GetStrength() const
{
    return 0;
}

unsigned
TreeCard::GetVitality() const
{
    return _vitality;
}

} // namespace

std::unique_ptr<Card>
Tree(unsigned cost, unsigned vitality)
{
    return std::make_unique<TreeCard>(cost, vitality);
}

} // namespace card
} // namespace cylvionpp
