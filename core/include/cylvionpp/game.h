#ifndef CYLVIONPP_GAME_H
#define CYLVIONPP_GAME_H

#include <memory>

namespace cylvionpp {
namespace core {

class Actor;
class Observer;
class Content;

class Game {
public:
    virtual bool Run() = 0;

    static std::unique_ptr<Game> New(std::shared_ptr<Actor>, std::shared_ptr<Observer>, std::unique_ptr<Content> &&);
};

} // namespace core
} // namespace cylvionpp

#endif // CYLVIONPP_GAME_H
