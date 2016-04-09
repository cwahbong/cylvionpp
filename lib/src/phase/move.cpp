#include "cylvionpp/phase.h"

#include "cylvionpp/dealer_helper.h"

namespace cylvionpp {
namespace phase {

namespace {

class MovePhase: public Phase {
public:
    std::unique_ptr<Phase> Action(Dealer & dealer, const Actor &) override;
};

std::unique_ptr<Phase>
MovePhase::Action(Dealer & dealer, const Actor &)
{
    if (!MoveLeftAllElementals(dealer)) {
        return nullptr;
    }
    return Draw();
}

} // namespace

std::unique_ptr<Phase>
Move()
{
    return std::make_unique<MovePhase>();
}

} // namespace phase
} // namespace cylvionpp
