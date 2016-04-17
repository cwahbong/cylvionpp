#include "summon.h"

namespace cylvionpp {
namespace phase {

namespace {

class Summon1Phase: public SummonPhase {
private:
    std::unique_ptr<Phase> NextPhase() override;
};

std::unique_ptr<Phase>
Summon1Phase::NextPhase()
{
    return Recuitment();
}

} // namespace

std::unique_ptr<Phase>
Summon1()
{
    return std::make_unique<Summon1Phase>();
}

} // namespace phase
} // namespace cylvionpp
