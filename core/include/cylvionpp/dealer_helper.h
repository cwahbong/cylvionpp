#ifndef CYLVIONPP_DEALER_HELPER_H
#define CYLVIONPP_DEALER_HELPER_H

#include <cstdlib>

namespace cylvionpp {
namespace core {

class Actor;
class Dealer;

bool MoveLeftAllElementals(Dealer & dealer);
bool DiscardChooseFromHand(Dealer & dealer, const Actor & actor);
bool ResolveSupport(Dealer & dealer, const Actor & actor, size_t row, size_t col);
bool ActRevealActions(Dealer & dealer, const Actor & actor);
bool ActDefendActions(Dealer & dealer, const Actor & actor);

} // namespace core
} // namespace cylvionpp

#endif // CYLVIONPP_DEALER_HELPER_H
