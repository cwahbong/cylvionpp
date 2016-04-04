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
#include "cylvionpp/stack.h"

namespace cylvionpp {

namespace {

class GameImpl: public Game {
public:
    GameImpl(std::shared_ptr<Actor>, std::shared_ptr<Observer>, std::unique_ptr<Content>);
    bool Run() override;

private:
    bool RavageStackHasRavage();
    bool FieldHasRavage();
    bool ResolveSupports(unsigned order);

    bool StartingDraw();

    bool Reveal();
    bool Move();
    bool Draw();
    bool Defend();
    bool LastMove();

    bool CheckWin();

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
    _dealer(Dealer::New(std::move(content), observer))
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
    for (Index r = 0; r < Field::row; ++r) {
        for (Index c = 0; c < Field::col; ++c) {
            const auto & card = field.Peek({r, c});
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
    const auto col = Field::col - 1;
    for (Index row = 0; row < Field::row; ++row) {
        const auto & peeked = field.Peek({row, col});
        if (peeked.IsNone() || peeked.GetPriority() != order) {
            continue;
        }
        if (!ResolveSupport(*_dealer, *_actor, {row, col})) {
            return false;
        }
    }
    return true;
}

bool
GameImpl::StartingDraw()
{
    return _dealer->Perform(*operation::PlayerDraw(8));
}

bool
GameImpl::Reveal()
{
    for (Index row = 0; row < Field::row; ++row) {
        if (!_dealer->Perform(*operation::RevealRavage(row))) {
            return false;
        }
    }
    if (!ActRevealActions(*_dealer, *_actor)) {
        return false;
    }
    for (unsigned i = 0; i < 4; ++i) {
        if (!ResolveSupports(i)) {
            return false;
        }
    }
    return true;
}

bool
GameImpl::Move()
{
    return MoveLeftAllElementals(*_dealer);
}

bool
GameImpl::Draw()
{
    return _dealer->Perform(*operation::PlayerDraw(3));
}

bool
GameImpl::Defend()
{
    if (!ActDefendActions(*_dealer, *_actor)) {
        return false;
    }
    const auto & hand = _dealer->GetContent().GetHand();
    while (hand.Size() > 10) {
        if (!DiscardChooseFromHand(*_dealer, *_actor)) {
            return false;
        }
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
GameImpl::CheckWin()
{
    return _dealer->GetContent().GetEdge() == 12;
}

bool
GameImpl::Run()
{
    if (!StartingDraw()) {
        return false;
    }
    while (RavageStackHasRavage()) {
        if (!Reveal() || !Move() || !Draw() || !Defend()) {
            return false;
        }
    }
    if (!LastMove()) {
        return false;
    }
    return CheckWin();
}

} // namespace

Game::~Game() = default;

std::unique_ptr<Game>
Game::New(
        std::shared_ptr<Actor> actor,
        std::shared_ptr<Observer> observer,
        std::unique_ptr<Content> && content)
{
    return std::make_unique<GameImpl>(actor, observer, std::move(content));
}

} // namespace cylvionpp
