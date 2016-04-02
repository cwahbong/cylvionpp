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
#include "cylvionpp/operation.h"
#include "cylvionpp/operation_factory.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {
namespace core {

namespace {

class GameImpl: public Game {
public:
    GameImpl(std::shared_ptr<Actor>, std::shared_ptr<Observer>, std::unique_ptr<Content>);
    bool Run() override;

private:
    bool RavageStackHasRavage();
    bool FieldHasRavage();
    bool ResolveSupports(unsigned order);

    bool Reveal();
    bool Move();
    bool Draw();
    bool Defend();
    bool LastMove();

    std::shared_ptr<Actor> _actor;
    std::shared_ptr<Observer> _observer;
    std::unique_ptr<Dealer> _dealer;
};

GameImpl::GameImpl(
        std::shared_ptr<Actor> actor,
        std::shared_ptr<Observer> observer,
        std::unique_ptr<Content> content):
    _actor(actor),
    _observer(observer),
    _dealer(Dealer::New(std::move(content), OperationFactory::New()))
{/* Empty.*/}

bool
GameImpl::RavageStackHasRavage()
{
    return !_dealer->GetContent().GetField().GetRavageStack(0).Empty();
}

bool
GameImpl::FieldHasRavage()
{
    const auto & field = _dealer->GetContent().GetField();
    for (size_t r = 0; r < Field::row; ++r) {
        for (size_t c = 0; c < Field::col; ++c) {
            const auto & card = field.Peek(r, c);
            if (card.IsRavage()) {
                return true;
            }
        }
    }
    return false;
}

bool
GameImpl::ResolveSupports(unsigned order)
{
    const auto & field = _dealer->GetContent().GetField();
    const size_t col = Field::col - 1;
    for (size_t row = 0; row < Field::row; ++row) {
        const auto & peeked = field.Peek(row, col);
        if (peeked.IsNone() || peeked.GetPriority() != order) {
            continue;
        }
        if (!ResolveSupport(*_dealer, *_actor, row, col)) {
            return false;
        }
    }
    return true;
}

bool
GameImpl::Reveal()
{
    for (size_t row = 0; row < Field::row; ++row) {
        _dealer->Perform(*_dealer->GetOperationFactory().RevealRavage(row));
    }
    if (!ActRevealActions(*_dealer, *_actor)) {
        return false;
    }
    for (unsigned i = 0; i < 4; ++i) {
        ResolveSupports(i);
    }
    return true;
}

bool
GameImpl::Move()
{
    MoveLeftAllElementals(*_dealer);
    return true;
}

bool
GameImpl::Draw()
{
    return _dealer->Perform(*_dealer->GetOperationFactory().PlayerDraw(3));
}

bool
GameImpl::Defend()
{
    if (!ActDefendActions(*_dealer, *_actor)) {
        return false;
    }
    const auto & hand = _dealer->GetContent().GetHand();
    while (hand.Size() > 10) {
        DiscardChooseFromHand(*_dealer, *_actor);
    }
    return true;
}

bool
GameImpl::LastMove()
{
    while (FieldHasRavage()) {
        if (!Move()) {
            return false;
        }
    }
    return true;
}

bool
GameImpl::Run()
{
    while (RavageStackHasRavage()) {
        if (!Reveal() || !Move() || !Draw() || !Defend()) {
            return false;
        }
    }
    if (!LastMove()) {
        return false;
    }
    return _dealer->GetContent().GetEdge() == 12;
}

} // namespace

Game::~Game()
{/* Empty. */}

std::unique_ptr<Game>
Game::New(
        std::shared_ptr<Actor> actor,
        std::shared_ptr<Observer> observer,
        std::unique_ptr<Content> && content)
{
    return std::make_unique<GameImpl>(actor, observer, std::move(content));
}

} // namespace core
} // namespace cylvionpp
