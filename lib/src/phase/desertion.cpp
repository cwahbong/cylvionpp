#include "cylvionpp/phase.h"

namespace cylvionpp {
namespace phase {

namespace {

class DesertionPhase: public Phase {
public:
    std::unique_ptr<Phase> Action(Dealer & dealer, const Actor &) override;
};

std::unique_ptr<Phase>
DesertionPhase::Action(Dealer & dealer, const Actor &)
{
    // TODO
    if (false) { // mobilization end
        return StartingDraw();
    }
    return Summon1();
}

} // namespace

std::unique_ptr<Phase>
Desertion()
{
    return std::make_unique<DesertionPhase>();
}

} // namespace phase
} // namespace cylvionpp
