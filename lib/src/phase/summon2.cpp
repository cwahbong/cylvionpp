#include "summon.h"

namespace cylvionpp {
namespace phase {

namespace {

class Summon2Phase: public SummonPhase {
private:
    std::unique_ptr<Phase> NextPhase() override;
};

std::unique_ptr<Phase>
Summon2Phase::NextPhase()
{
    return Desertion();
}

} // namespace

std::unique_ptr<Phase>
Summon2()
{
    return std::make_unique<Summon2Phase>();
}

} // namespace phase
} // namespace cylvionpp
