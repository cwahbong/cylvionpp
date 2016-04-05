#ifndef CYLVIONPP_INTRO_H
#define CYLVIONPP_INTRO_H

#include "cylvionpp_export.h"

#include <memory>

namespace cylvionpp {

class CardFactory;
class Content;

std::unique_ptr<Content>
CYLVIONPP_EXPORT MakeIntroContent();

// TODO MakeFullGame

} // namespace cylvionpp

#endif // CYLVIONPP_INTRO_H
