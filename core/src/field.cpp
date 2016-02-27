#include "cylvionpp/field.h"

#include <algorithm>
#include <array>

#include "cylvionpp/card.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {
namespace core {

namespace {

class FieldImpl: public Field {
public:
    FieldImpl();

    bool Empty() const override;

    const std::unique_ptr<Card> & Peek(size_t row, size_t col) const override;
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
};

FieldImpl::FieldImpl():
    c(),
    s()
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

const std::unique_ptr<Card> &
FieldImpl::Peek(size_t row, size_t col) const
{
    return c[row][col];
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

} // namespace core
} // namespace cylvionpp
