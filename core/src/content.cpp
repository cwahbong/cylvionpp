#include "cylvionpp/content.h"

#include "cylvionpp/field.h"
#include "cylvionpp/hand.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {
namespace core {

namespace {

class ContentImpl: public Content {
public:
    ContentImpl();

    unsigned GetEdge() const override { return _edge; }
    void IncreaseEdge(unsigned amount) override { _edge += amount; }
    void DecreaseEdge(unsigned amount) override;
    void SetEdge(unsigned edge) override { _edge = edge; }

    unsigned GetMana() const override { return _mana; }
    void SetMana(unsigned mana) override { _mana = mana; }

    const Field & GetField() const override { return *_field; }
    Field & GetField() override { return *_field; }

    const Hand & GetHand() const override { return *_hand; }
    Hand & GetHand() override { return *_hand; }

    const Stack & GetDiscarded() const override { return *_discarded; }
    Stack & GetDiscarded() override { return *_discarded; }

    const Stack & GetUndrawn() const override { return *_undrawn; }
    Stack & GetUndrawn() override { return *_undrawn; }

private:
    unsigned _edge;
    unsigned _mana;
    std::unique_ptr<Field> _field;
    std::unique_ptr<Hand> _hand;
    std::unique_ptr<Stack> _discarded;
    std::unique_ptr<Stack> _undrawn;
};

ContentImpl::ContentImpl():
    _edge(0),
    _mana(0),
    _field(Field::New()),
    _hand(Hand::New()),
    _discarded(Stack::New()),
    _undrawn(Stack::New())
{/* Empty. */}

void
ContentImpl::DecreaseEdge(unsigned amount)
{
    if (amount > _edge) {
        throw "lose";
    }
    _edge -= amount;
}

} // namespace

Content::~Content() = default;

std::unique_ptr<Content>
Content::New()
{
    return std::make_unique<ContentImpl>();
}

} // namespace core
} // namespace cylvionpp
