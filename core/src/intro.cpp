#include "cylvionpp/intro.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/field.h"
#include "cylvionpp/game.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {
namespace core {

std::unique_ptr<Content>
MakeIntroContent()
{
    auto content = Content::New();
    content->SetEdge(6);
    auto & undrawn = content->GetUndrawn();
    for (int i = 0; i < 4; ++i) {
        undrawn.Push(Card::NewFountain(0, 1));
        undrawn.Push(Card::NewFountain(1, 2));
        undrawn.Push(Card::NewFountain(2, 3));
        undrawn.Push(Card::NewFountain(3, 4));
        undrawn.Push(Card::NewTree(0, 1));
        undrawn.Push(Card::NewTree(1, 2));
        undrawn.Push(Card::NewTree(2, 3));
        undrawn.Push(Card::NewTree(3, 4));
        undrawn.Push(Card::NewWhale());
        undrawn.Push(Card::NewElephant());
        undrawn.Push(Card::NewHedgehogs());
        undrawn.Push(Card::NewOwl());
    }
    auto allRavages = Stack::New();
    for (int i = 0; i < 8; ++i) {
        allRavages->Push(Card::NewElemental(0, 4));
        allRavages->Push(Card::NewElemental(1, 2));
        allRavages->Push(Card::NewElemental(2, 3));
        allRavages->Push(Card::NewElemental(3, 4));
        allRavages->Push(Card::NewBlaze());
        allRavages->Push(Card::NewSimoon());
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

} // namespace core
} // namespace cylvionpp
