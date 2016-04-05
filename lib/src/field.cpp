#include "cylvionpp/field.h"

#include <algorithm>
#include <array>

#include "cylvionpp/card.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {

namespace {

class FieldImpl: public Field {
public:
    FieldImpl();

    bool Empty() const override;

    const Card & Peek(const Location & location) const override;
    Card & Peek(const Location & location) override;
    bool Put(const Location & location, std::unique_ptr<Card> &&) override;
    bool Move(const Location & from, const Location & to) override;
    std::unique_ptr<Card> Remove(const Location & location) override;

    const Stack & GetRavageStack(Index row) const override;
    Stack & GetRavageStack(Index row) override;

private:
    using Row = std::array<std::unique_ptr<Card>, 5>;
    static bool RowEmpty(const Row &);

    std::array<Row, 4> c;
    std::array<std::unique_ptr<Stack>, 4> s;
    std::unique_ptr<Card> e;
};

FieldImpl::FieldImpl():
    c(),
    s(),
    e(card::None())
{
    for (auto && stack: s) {
        stack = Stack::New();
    }
}

bool
FieldImpl::RowEmpty(const FieldImpl::Row & row)
{
    return std::none_of(row.begin(), row.end(), [](const std::unique_ptr<Card> & card){ return card.get(); });
}

bool
FieldImpl::Empty() const
{
    return std::all_of(c.begin(), c.end(), FieldImpl::RowEmpty);
}

const Card &
FieldImpl::Peek(const Location & location) const
{
    const auto & peeked = c[location.row][location.col];
    return peeked ? *peeked : *e;
}

Card &
FieldImpl::Peek(const Location & location)
{
    return const_cast<Card &>(static_cast<const FieldImpl *>(this)->Peek(location));
}

bool
FieldImpl::Put(const Location & location, std::unique_ptr<Card> && card)
{
    if (c[location.row][location.col].get()) {
        return false;
    }
    c[location.row][location.col] = std::move(card);
    return true;
}

bool
FieldImpl::Move(const Location & from, const Location & to)
{
    if (!c[from.row][from.col].get() || c[to.row][to.col].get()) {
        return false;
    }
    c[to.row][to.col] = std::move(c[from.row][from.col]);
    return true;
}

std::unique_ptr<Card>
FieldImpl::Remove(const Location & location)
{
    if (!c[location.row][location.col]) {
        throw std::logic_error("Remove null card.");
    }
    return std::move(c[location.row][location.col]);
}

const Stack &
FieldImpl::GetRavageStack(Index row) const
{
    return *s[row];
}


Stack &
FieldImpl::GetRavageStack(Index row)
{
    return const_cast<Stack &>(static_cast<const FieldImpl *>(this)->GetRavageStack(row));
}

} // namespace

Field::~Field()
{/* Empty. */}

std::unique_ptr<Field>
Field::New()
{
    return std::make_unique<FieldImpl>();
}

void
MoveElemental(Field & field, const Location & from, const Location & to)
{
    const auto & movingCard = field.Peek(from);
    if (!movingCard.IsRavage()) {
        throw std::logic_error("should be an elemental");
    }
    bool elementalAlive = true;
    const auto & destCard = field.Peek(to);
    if (destCard.IsCylvan()) {
        if (movingCard.GetStrength() <= destCard.GetStrength()) {
            elementalAlive = false;
        }
        if (movingCard.GetStrength() >= destCard.GetStrength()) {
            field.Remove(to);
        }
    }
    if (elementalAlive) {
        field.Move(from, to);
    } else {
        field.Remove(from);
    }
}

} // namespace cylvionpp
