#include "ravage.h"

namespace cylvionpp {
namespace card {

namespace {

class ElementalCard: public RavageCard {
public:
    ElementalCard(bool enhanced, unsigned strength, unsigned enhancedStrength);
    unsigned GetStrength() const override;
    unsigned GetPriority() const override;

    bool IsBlazing() const override;
    void SetBlaze() override;

    bool OnBeforeMove(Dealer &, const Actor &, const Location &) const override;

private:
    bool _enhanced;
    unsigned _strength;
    unsigned _enhancedStrength;
};

ElementalCard::ElementalCard(bool enhanced, unsigned strength, unsigned enhancedStrength):
    _enhanced(enhanced),
    _strength(strength),
    _enhancedStrength(enhancedStrength)
{/* Empty. */}

unsigned
ElementalCard::GetStrength() const
{
    return _enhanced ? _enhancedStrength : _strength;
}

unsigned
ElementalCard::GetPriority() const
{
    return 4;
}

bool
ElementalCard::IsBlazing() const
{
    return _enhanced;
}

void
ElementalCard::SetBlaze()
{
    _enhanced = true;
}

bool
ElementalCard::OnBeforeMove(Dealer &, const Actor &, const Location &) const
{
    return true;
}

} // namespace

std::unique_ptr<Card>
Elemental(unsigned strength, unsigned enhancedStrength)
{
    return std::make_unique<ElementalCard>(false, strength, enhancedStrength);
}

} // namespace card
} // namespace cylvionpp
