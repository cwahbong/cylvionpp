#ifndef CYLVIONPP_DEALER_HELPER_H
#define CYLVIONPP_DEALER_HELPER_H

#include <cstdlib>

namespace cylvionpp {

class Actor;
class Dealer;

bool MoveLeftAllElementals(Dealer & dealer);
bool DiscardChooseFromHand(Dealer & dealer, const Actor & actor);
bool ResolveSupport(Dealer & dealer, const Actor & actor, size_t row, size_t col);

} // namespace cylvionpp

#endif // CYLVIONPP_DEALER_HELPER_H
