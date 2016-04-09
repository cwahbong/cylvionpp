#include "cylvionpp/phase.h"

#include "cylvionpp/dealer.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {
namespace phase {

namespace {

class StartingDrawPhase: public Phase {
public:
    std::unique_ptr<Phase> Action(Dealer & dealer, const Actor &) override;
};

std::unique_ptr<Phase>
StartingDrawPhase::Action(Dealer & dealer, const Actor &)
{
    dealer.Perform(*operation::PlayerDraw(8));
    return Reveal();
}

} // namespace

std::unique_ptr<Phase>
StartingDraw()
{
    return std::make_unique<StartingDrawPhase>();
}

} // namespace phase
} // namespace cylvionpp
