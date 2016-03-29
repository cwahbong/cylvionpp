#include "cylvionpp/field.h"

#include <algorithm>
#include <array>

#include "cylvionpp/card.h"
#include "cylvionpp/card_factory.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {
namespace core {

namespace {

class FieldImpl: public Field {
public:
    FieldImpl();

    bool Empty() const override;

    const Card & Peek(size_t row, size_t col) const override;
    Card & Peek(size_t row, size_t col) override;
    bool Put(size_t row, size_t col, std::unique_ptr<Card> &&) override;
    bool Move(size_t row, size_t col, size_t to_row, size_t toCol) override;
    std::unique_ptr<Card> Remove(size_t row, size_t col) override;

    const Stack & GetRavageStack(size_t row) const override;
    Stack & GetRavageStack(size_t row) override;

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
    e(NewCardFactory()->NewNone())
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
FieldImpl::Peek(size_t row, size_t col) const
{
    const auto & peeked = c[row][col];
    return peeked ? *peeked : *e;
}

Card &
FieldImpl::Peek(size_t row, size_t col)
{
    return const_cast<Card &>(static_cast<const FieldImpl *>(this)->Peek(row, col));
}

bool
FieldImpl::Put(size_t row, size_t col, std::unique_ptr<Card> && card)
{
    if (c[row][col].get()) {
        return false;
    }
    c[row][col] = std::move(card);
    return true;
}

bool
FieldImpl::Move(size_t row, size_t col, size_t toRow, size_t toCol)
{
    if (!c[row][col].get() || c[toRow][toCol].get()) {
        return false;
    }
    c[toRow][toCol] = std::move(c[row][col]);
    return true;
}

std::unique_ptr<Card>
FieldImpl::Remove(size_t row, size_t col)
{
    if (!c[row][col]) {
        throw std::logic_error("Remove null card.");
    }
    return std::move(c[row][col]);
}

const Stack &
FieldImpl::GetRavageStack(size_t row) const
{
    return *s[row];
}


Stack &
FieldImpl::GetRavageStack(size_t row)
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
MoveElemental(Field & field, size_t fromRow, size_t fromCol,
                     size_t toRow, size_t toCol)
{
    const auto & movingCard = field.Peek(fromRow, fromCol);
    if (!movingCard.IsRavage()) {
        throw std::logic_error("should be an elemental");
    }
    bool elementalAlive = true;
    const auto & destCard = field.Peek(toRow, toCol);
    if (destCard.IsCylvan()) {
        if (movingCard.GetStrength() <= destCard.GetStrength()) {
            elementalAlive = false;
        }
        if (movingCard.GetStrength() >= destCard.GetStrength()) {
            field.Remove(toRow, toCol);
        }
    }
    if (elementalAlive) {
        field.Move(fromRow, fromCol, toRow, toCol);
    } else {
        field.Remove(fromRow, fromCol);
    }
}

} // namespace core
} // namespace cylvionpp
