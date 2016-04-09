#include "cylvionpp/phase.h"

#include "cylvionpp/dealer.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {
namespace phase {

namespace {

class DrawPhase: public Phase {
public:
    std::unique_ptr<Phase> Action(Dealer & dealer, const Actor &) override;
};

std::unique_ptr<Phase>
DrawPhase::Action(Dealer & dealer, const Actor &)
{
    if (!dealer.Perform(*operation::PlayerDraw(3))) {
        return nullptr;
    }
    return Defend();
}

} // namespace

std::unique_ptr<Phase>
Draw()
{
    return std::make_unique<DrawPhase>();
}

} // namespace phase
} // namespace cylvionpp
