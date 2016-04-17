#include "cylvionpp/phase.h"

namespace cylvionpp {
namespace phase {

namespace {

class RecuitmentPhase: public Phase {
public:
    std::unique_ptr<Phase> Action(Dealer & dealer, const Actor &) override;
};

std::unique_ptr<Phase>
RecuitmentPhase::Action(Dealer & dealer, const Actor &)
{
    // TODO
    return Summon2();
}

} // namespace

std::unique_ptr<Phase>
Recuitment()
{
    return std::make_unique<RecuitmentPhase>();
}

} // namespace phase
} // namespace cylvionpp
