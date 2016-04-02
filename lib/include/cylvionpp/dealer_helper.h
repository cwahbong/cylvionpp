#ifndef CYLVIONPP_DEALER_HELPER_H
#define CYLVIONPP_DEALER_HELPER_H

#include "cylvionpp_export.h"

#include <cstdlib>

namespace cylvionpp {

class Actor;
class Dealer;

CYLVIONPP_EXPORT bool MoveLeftAllElementals(Dealer & dealer);
CYLVIONPP_EXPORT bool DiscardChooseFromHand(Dealer & dealer, const Actor & actor);
CYLVIONPP_EXPORT bool ResolveSupport(Dealer & dealer, const Actor & actor, size_t row, size_t col);

} // namespace cylvionpp

#endif // CYLVIONPP_DEALER_HELPER_H
