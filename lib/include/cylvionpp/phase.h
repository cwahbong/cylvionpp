#ifndef CYLVIONPP_PHASE_H
#define CYLVIONPP_PHASE_H

#include "cylvionpp_export.h"
#include "types.h"

#include <memory>

namespace cylvionpp {

class Actor;
class Content;
class Dealer;

class CYLVIONPP_EXPORT Phase {
public:
    virtual ~Phase() = 0;

    virtual std::unique_ptr<Phase> Action(Dealer & dealer, const Actor & actor) = 0;
};

namespace phase {

CYLVIONPP_EXPORT std::unique_ptr<Phase> StartingDraw();
CYLVIONPP_EXPORT std::unique_ptr<Phase> Reveal();
CYLVIONPP_EXPORT std::unique_ptr<Phase> Move();
CYLVIONPP_EXPORT std::unique_ptr<Phase> Draw();
CYLVIONPP_EXPORT std::unique_ptr<Phase> Defend();
CYLVIONPP_EXPORT std::unique_ptr<Phase> LastMove();

} // namespace phase

} // namespace cylvionpp

#endif // CYLVIONPP_PHASE_H
