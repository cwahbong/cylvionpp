#include "cylvionpp/game.h"

#include <sstream>
#include <utility>

#include "cylvionpp/actor.h"
#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/content_helper.h"
#include "cylvionpp/field.h"
#include "cylvionpp/hand.h"
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
    std::unique_ptr<Content> _content;
};

GameImpl::GameImpl(
        std::shared_ptr<Actor> actor,
        std::shared_ptr<Observer> observer,
        std::unique_ptr<Content> content):
    _actor(actor),
    _observer(observer),
    _content(std::move(content))
{/* Empty.*/}

bool
GameImpl::RavageStackHasRavage()
{
    return !_content->GetField().GetRavageStack(0).Empty();
}

bool
GameImpl::FieldHasRavage()
{
    Field & field = _content->GetField();
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
    auto & field = _content->GetField();
    size_t col = Field::col - 1;
    for (size_t row = 0; row < Field::row; ++row) {
        const auto & peeked = field.Peek(row, col);
        if (peeked.IsNone() || peeked.GetPriority() != order) {
            continue;
        }
        auto card = field.Remove(row, col);
        if (!Card::OnBeforeMove(std::move(card), *_content, *_actor)) {
            return false;
        }
        if (card) {
            field.Put(row, col, std::move(card));
        }
    }
    return true;
}

bool
GameImpl::Reveal()
{
    Field & field = _content->GetField();
    for (size_t row = 0; row < Field::row; ++row) {
        Stack & ravage = field.GetRavageStack(row);
        field.Put(row, Field::col - 1, ravage.Pop());
    }
    if (!ActRevealActions(*_content, *_actor)) {
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
    MoveLeftAllElementals(*_content);
    return true;
}

bool
GameImpl::Draw()
{
    for (int i = 0; i < 3; ++i) {
        PlayerDraw(*_content);
    }
    return true;
}

bool
GameImpl::Defend()
{
    if (!ActDefendActions(*_content, *_actor)) {
        return false;
    }
    const auto & hand = _content->GetHand();
    while (hand.Size() > 10) {
        DiscardChooseFromHand(*_content, *_actor);
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
    StartingShuffle(*_content);
    while (RavageStackHasRavage()) {
        if (!Reveal() || !Move() || !Draw() || !Defend()) {
            return false;
        }
    }
    if (!LastMove()) {
        return false;
    }
    return _content->GetEdge() == 12;
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
