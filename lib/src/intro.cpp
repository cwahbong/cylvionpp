#include "cylvionpp/intro.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/field.h"
#include "cylvionpp/game.h"
#include "cylvionpp/phase.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {

std::unique_ptr<Content>
MakeIntroContent()
{
    auto content = Content::New();
    content->SetEdge(6);
    auto & undrawn = content->GetUndrawn();
    for (int i = 0; i < 4; ++i) {
        undrawn.Push(card::Fountain(0, 1));
        undrawn.Push(card::Fountain(1, 2));
        undrawn.Push(card::Fountain(2, 3));
        undrawn.Push(card::Fountain(3, 4));
        undrawn.Push(card::Tree(0, 1));
        undrawn.Push(card::Tree(1, 2));
        undrawn.Push(card::Tree(2, 3));
        undrawn.Push(card::Tree(3, 4));
        undrawn.Push(card::Whale());
        undrawn.Push(card::Elephant());
        undrawn.Push(card::Hedgehogs());
        undrawn.Push(card::Owl());
    }
    auto allRavages = Stack::New();
    for (int i = 0; i < 8; ++i) {
        allRavages->Push(card::Elemental(0, 4));
        allRavages->Push(card::Elemental(1, 2));
        allRavages->Push(card::Elemental(2, 3));
        allRavages->Push(card::Elemental(3, 4));
        allRavages->Push(card::Blaze());
        allRavages->Push(card::Simoon());
    }
    if (allRavages->Size() % 4 != 0) {
        return nullptr;
    }
    auto ravageSize = allRavages->Size() / 4;
    auto & field = content->GetField();
    for (int i = 0; i < 4; ++i) {
        auto & ravage = field.GetRavageStack(i);
        for (decltype(ravageSize) j = 0; j < ravageSize; ++j) {
            ravage.Push(allRavages->Pop());
        }
    }
    if (allRavages->Size() != 0) {
        return nullptr;
    }
    return content;
}

std::unique_ptr<Game>
MakeIntroGame(std::shared_ptr<Actor> actor, std::shared_ptr<Observer> observer)
{
    return Game::New(actor, observer, phase::StartingDraw(), MakeIntroContent());
}

} // namespace cylvionpp
