#ifndef CYLVIONPP_GAME_H
#define CYLVIONPP_GAME_H

#include "cylvionpp_export.h"

#include <memory>

namespace cylvionpp {

class Actor;
class Content;
class Observer;
class Phase;

class CYLVIONPP_EXPORT Game {
public:
    virtual ~Game() = 0;

    virtual bool Run() = 0;

    static std::unique_ptr<Game> New(std::shared_ptr<Actor>, std::shared_ptr<Observer>, std::unique_ptr<Phase>, std::unique_ptr<Content>);
};

} // namespace cylvionpp

#endif // CYLVIONPP_GAME_H
