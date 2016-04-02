#include "cylvionpp/intro.h"

#include "cylvionpp/card.h"
#include "cylvionpp/card_factory.h"
#include "cylvionpp/content.h"
#include "cylvionpp/field.h"
#include "cylvionpp/game.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {

std::unique_ptr<Content>
MakeIntroContent(CardFactory & cardFactory)
{
    auto content = Content::New();
    content->SetEdge(6);
    auto & undrawn = content->GetUndrawn();
    for (int i = 0; i < 4; ++i) {
        undrawn.Push(cardFactory.NewFountain(0, 1));
        undrawn.Push(cardFactory.NewFountain(1, 2));
        undrawn.Push(cardFactory.NewFountain(2, 3));
        undrawn.Push(cardFactory.NewFountain(3, 4));
        undrawn.Push(cardFactory.NewTree(0, 1));
        undrawn.Push(cardFactory.NewTree(1, 2));
        undrawn.Push(cardFactory.NewTree(2, 3));
        undrawn.Push(cardFactory.NewTree(3, 4));
        undrawn.Push(cardFactory.NewWhale());
        undrawn.Push(cardFactory.NewElephant());
        undrawn.Push(cardFactory.NewHedgehogs());
        undrawn.Push(cardFactory.NewOwl());
    }
    auto allRavages = Stack::New();
    for (int i = 0; i < 8; ++i) {
        allRavages->Push(cardFactory.NewElemental(0, 4));
        allRavages->Push(cardFactory.NewElemental(1, 2));
        allRavages->Push(cardFactory.NewElemental(2, 3));
        allRavages->Push(cardFactory.NewElemental(3, 4));
        allRavages->Push(cardFactory.NewBlaze());
        allRavages->Push(cardFactory.NewSimoon());
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

} // namespace cylvionpp
