#include "cylvionpp/game.h"

#include <sstream>
#include <utility>

#include "cylvionpp/actor.h"
#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/content_helper.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/dealer_helper.h"
#include "cylvionpp/field.h"
#include "cylvionpp/hand.h"
#include "cylvionpp/phase.h"
#include "cylvionpp/operation.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {

namespace {

class GameImpl: public Game {
public:
    GameImpl(std::shared_ptr<Actor>, std::shared_ptr<Observer>, std::unique_ptr<Phase>, std::unique_ptr<Content>);
    bool Run() override;

private:
    bool CheckWin();

    std::shared_ptr<Actor> _actor;
    std::unique_ptr<Dealer> _dealer;
    std::unique_ptr<Phase> _phase;
};

GameImpl::GameImpl(
        std::shared_ptr<Actor> actor,
        std::shared_ptr<Observer> observer,
        std::unique_ptr<Phase> phase,
        std::unique_ptr<Content> content):
    _actor(actor),
    _dealer(Dealer::New(std::move(content), observer)),
    _phase(std::move(phase))
{/* Empty.*/}

bool
GameImpl::CheckWin()
{
    return _dealer->GetContent().GetEdge() == 12;
}

bool
GameImpl::Run()
{
    while (_phase) {
        _phase = _phase->Action(*_dealer, *_actor);
    }
    return CheckWin();
}

} // namespace

Game::~Game() = default;

std::unique_ptr<Game>
Game::New(
        std::shared_ptr<Actor> actor,
        std::shared_ptr<Observer> observer,
        std::unique_ptr<Phase> phase,
        std::unique_ptr<Content> content)
{
    return std::make_unique<GameImpl>(actor, observer, std::move(phase), std::move(content));
}

} // namespace cylvionpp
