#include "cylvionpp/card.h"

namespace cylvionpp {
namespace card {

namespace {

class NoneCard: public Card {
public:
    std::string GetName() const override { return "none"; }
    unsigned GetCost() const override { throw std::logic_error("None"); }
    unsigned GetStrength() const override { throw std::logic_error("None"); }
    unsigned GetVitality() const override { throw std::logic_error("None"); }
    unsigned GetPriority() const override { throw std::logic_error("None"); }

    bool IsCylvan() const override { return false; }
    bool IsTree() const override { return false; }
    bool IsRavage() const override { return false; }
    bool IsBlazing() const override { return false; }
    bool IsNone() const override { return true; }

    void SetBlaze() override {/* Empty. */}

    bool OnBeforeMove(Dealer &, const Actor &, const Location &) const override { throw std::logic_error("None"); }
    bool OnUseWhenReveal(Dealer &, const Actor &, Index) const override { throw std::logic_error("None"); }
    bool OnUseWhenDefend(Dealer &, const Actor &, Index) const override { throw std::logic_error("None"); }
};

} // namespace

std::unique_ptr<Card>
None()
{
    return std::make_unique<NoneCard>();
}

} // namespace card
} // namespace cylvionpp
