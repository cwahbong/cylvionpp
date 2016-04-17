#include "cylvionpp/phase.h"

#include "cylvionpp/content.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/desertions.h"
#include "cylvionpp/operation.h"
#include "cylvionpp/stack.h"

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
    bool mobilizationEnd = false;
    const auto & content = dealer.GetContent();
    const auto & desertions = content.GetDesertions();
    auto col = desertions.Peek();

    auto & recuitment = content.GetRecuitment(col);
    mobilizationEnd |= content.GetSylvan().Empty() && recuitment.Empty();
    dealer.Perform(*operation::RemoveRecuitment(col));

    mobilizationEnd |= desertions.Empty();
    if (mobilizationEnd) {
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
