#include "cylvionpp/game.h"

#include <sstream>
#include <utility>

#include "cylvionpp/actor.h"
#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
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

    void InitShuffle();
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
            auto & card = field.Peek(r, c);
            if (card && card->IsRavage()) {
                return true;
            }
        }
    }
    return false;
}

void
GameImpl::InitShuffle()
{
    _content->GetUndrawn().Shuffle();
    for (size_t i = 0; i < Field::row; ++i) {
        _content->GetField().GetRavageStack(i).Shuffle();
    }
}

bool
GameImpl::Reveal()
{
    Field & field = _content->GetField();
    for (size_t row = 0; row < Field::row; ++row) {
        Stack & ravage = field.GetRavageStack(row);
        field.Put(row, Field::col - 1, ravage.Pop());
    }
    Hand & hand = _content->GetHand();
    Stack & discarded = _content->GetDiscarded();
    while (true) {
        Action action = _actor->DefendAction(*_content);
        if (action.end) {
            break;
        }
        if (action.additional["type"] == "discard") {
            size_t idx;
            std::stringstream ss(action.additional["idx"]);
            ss >> idx;
            std::unique_ptr<Card> card = hand.Remove(idx);
            if (!card) {
                // TODO bad input
                continue;
            }
            discarded.Push(std::move(card));
            _content->SetMana(_content->GetMana() + 1);
        } else if (action.additional["type"] == "use") {
            size_t idx;
            std::stringstream ss(action.additional["idx"]);
            ss >> idx;
            std::unique_ptr<Card> card = hand.Remove(idx);
            if (!card) {
                // TODO bad input
                continue;
            }
            if (!Card::OnBeforeMove(std::move(card), *_content, *_actor)) {
                hand.Add(std::move(card));
            }
        }
    }
    for (size_t row = 0; row < Field::row; ++row) {
        for (size_t col = 0; col < Field::col; ++col) {
            const auto & peeked = field.Peek(row, col);
            if (!peeked) {
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
    }
    return true;
}

bool
GameImpl::Move()
{
    Field & field = _content->GetField();
    for (size_t row = 0; row < Field::row; ++row) {
        for (size_t col = 0; col < Field::col; ++col) {
            const std::unique_ptr<Card> & card = field.Peek(row, col);
            if (!card || card->IsCylvan()) {
                continue;
            }
            if (col == 0) {
                if (card->GetStrength() >= _content->GetEdge()) {
                    return false;
                }
                _content->SetEdge(_content->GetEdge() - card->GetStrength());
                field.Remove(row, col);
            } else {
                const auto & leftCard = field.Peek(row, col - 1);
                if (leftCard && leftCard->IsCylvan()) {
                    if (leftCard->GetStrength() > card->GetStrength()) {
                        field.Remove(row, col);
                    } else {
                        field.Remove(row, col - 1);
                        if (leftCard->GetStrength() < card->GetStrength()) {
                            field.Move(row, col, row, col - 1);
                        } else {
                            field.Remove(row, col);
                        }
                    }
                } else {
                    field.Move(row, col, row, col - 1);
                }
            }
        }
    }
    return true;
}

bool
GameImpl::Draw()
{
    Stack & undrawn = _content->GetUndrawn();
    Hand & hand = _content->GetHand();
    for (int i = 0; i < 3; ++i) {
        if (undrawn.Empty()) {
            Stack & discarded = _content->GetDiscarded();
            while (!discarded.Empty()) {
                undrawn.Push(discarded.Pop());
            }
            undrawn.Shuffle();
        }
        hand.Add(undrawn.Pop());
    }
    return true;
}

bool
GameImpl::Defend()
{
    Hand & hand = _content->GetHand();
    Stack & discarded = _content->GetDiscarded();
    while (true) {
        Action action = _actor->DefendAction(*_content);
        if (action.end) {
            break;
        }
        if (action.additional["type"] == "discard") {
            size_t idx;
            std::stringstream ss(action.additional["idx"]);
            ss >> idx;
            std::unique_ptr<Card> card = hand.Remove(idx);
            if (!card) {
                // TODO bad input
                continue;
            }
            discarded.Push(std::move(card));
            _content->SetMana(_content->GetMana() + 1);
        } else if (action.additional["type"] == "use") {
            size_t idx;
            std::stringstream ss(action.additional["idx"]);
            ss >> idx;
            std::unique_ptr<Card> card = hand.Remove(idx);
            if (!card) {
                // TODO bad input
                continue;
            }
            if (!Card::OnUse(std::move(card), *_content, *_actor)) {
                hand.Add(std::move(card));
            }
        }
    }
    while (hand.Size() > 10) {
        size_t idx = _actor->AnswerIndex("discard hand");
        discarded.Push(hand.Remove(idx));
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
    InitShuffle();
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
