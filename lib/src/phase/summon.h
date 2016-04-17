#ifndef CYLVIONPP_INTERNAL_SUMMON_H
#define CYLVIONPP_INTERNAL_SUMMON_H

#include "cylvionpp/phase.h"

namespace cylvionpp {

class SummonPhase: public Phase {
public:
    std::unique_ptr<Phase> Action(Dealer &, const Actor &) override;

private:
    virtual std::unique_ptr<Phase> NextPhase() = 0;
};

} // namespace cylvionpp

#endif // CYLVIONPP_INTERNAL_SUMMON_H
