#ifndef CYLVIONPP_INTRO_H
#define CYLVIONPP_INTRO_H

#include "cylvionpp_export.h"

#include <memory>

namespace cylvionpp {

class Actor;
class Content;
class Game;
class Observer;

std::unique_ptr<Content>
CYLVIONPP_EXPORT MakeIntroContent();

std::unique_ptr<Game>
CYLVIONPP_EXPORT MakeIntroGame(std::shared_ptr<Actor>, std::shared_ptr<Observer>);

// TODO MakeFullGame

} // namespace cylvionpp

#endif // CYLVIONPP_INTRO_H
