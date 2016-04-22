#ifndef CYLVIONPP_CONTENT_HELPER_H
#define CYLVIONPP_CONTENT_HELPER_H

#include "cylvionpp_export.h"
#include "types.h"

#include <cstdlib>

namespace cylvionpp {

class Actor;
class Content;
class Dealer;

CYLVIONPP_EXPORT void StartingShuffle(Content & content);
CYLVIONPP_EXPORT bool ActRevealActions(Dealer & dealer, const Actor & actor);
CYLVIONPP_EXPORT bool ActDefendActions(Dealer & dealer, const Actor & actor);
CYLVIONPP_EXPORT Index RandomHandIndex(const Content & content);

} // namespace cylvionpp

#endif // CYLVIONPP_CONTENT_HELPER_H
