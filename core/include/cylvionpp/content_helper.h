#ifndef CYLVIONPP_CONTENT_HELPER_H
#define CYLVIONPP_CONTENT_HELPER_H

#include <cstdlib>

namespace cylvionpp {
namespace core {

class Actor;
class Content;
class Dealer;

void StartingShuffle(Content & content);
bool ActRevealActions(Dealer & dealer, const Actor & actor);
bool ActDefendActions(Dealer & dealer, const Actor & actor);

} // namespace core
} // namespace cylvionpp

#endif // CYLVIONPP_CONTENT_HELPER_H
