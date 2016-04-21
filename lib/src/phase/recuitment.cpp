#include "cylvionpp/phase.h"

#include "cylvionpp/actor.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {
namespace phase {

namespace {

class RecuitmentPhase: public Phase {
public:
    std::unique_ptr<Phase> Action(Dealer & dealer, const Actor & actor) override;
};

std::unique_ptr<Phase>
RecuitmentPhase::Action(Dealer & dealer, const Actor & actor)
{
    const auto idx = actor.AnswerIndex("recuit row", dealer.GetContent());
    dealer.Perform(*operation::TakeRecuitment(idx));
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
