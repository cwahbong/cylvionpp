#include "cylvionpp/content.h"

#include "cylvionpp/desertions.h"
#include "cylvionpp/field.h"
#include "cylvionpp/hand.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {

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

    const Stack & GetRecuitment(Index col) const override { return *_recuitment[col]; }
    Stack & GetRecuitment(Index col) override { return *_recuitment[col]; }

    const Stack & GetSylvan() const override { return *_sylvan; }
    Stack & GetSylvan() override { return *_sylvan; }

    const Desertions & GetDesertions() const override { return *_desertions; }
    Desertions & GetDesertions() override { return *_desertions;}

    const Hand & GetDiscarded() const override { return *_discarded; }
    Hand & GetDiscarded() override { return *_discarded; }

    const Stack & GetUndrawn() const override { return *_undrawn; }
    Stack & GetUndrawn() override { return *_undrawn; }

private:
    unsigned _edge;
    unsigned _mana;
    std::unique_ptr<Field> _field;
    std::unique_ptr<Hand> _hand;
    std::array<std::unique_ptr<Stack>, 4> _recuitment;
    std::unique_ptr<Stack> _sylvan;
    std::unique_ptr<Desertions> _desertions;
    std::unique_ptr<Hand> _discarded;
    std::unique_ptr<Stack> _undrawn;
};

ContentImpl::ContentImpl():
    _edge(0),
    _mana(0),
    _field(Field::New()),
    _hand(Hand::New()),
    _recuitment(),
    _sylvan(Stack::New()),
    _desertions(Desertions::New()),
    _discarded(Hand::New()),
    _undrawn(Stack::New())
{
    for (auto && stack: _recuitment) {
        stack = Stack::New();
    }
}

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

bool
operator==(const Content & lhs, const Content & rhs)
{
    return lhs.GetEdge() == rhs.GetEdge() &&
        lhs.GetMana() == rhs.GetMana() &&
        lhs.GetField() == rhs.GetField() &&
        lhs.GetHand() == rhs.GetHand() &&
        lhs.GetDiscarded() == rhs.GetDiscarded() &&
        lhs.GetUndrawn() == rhs.GetUndrawn();
}

bool
operator!=(const Content & lhs, const Content & rhs)
{
    return !(lhs == rhs);
}

} // namespace cylvionpp
