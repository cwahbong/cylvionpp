#include "support.h"

#include "cylvionpp/field.h"

namespace cylvionpp {
namespace card {

namespace {

class BlazeCard: public SupportCard {
    unsigned GetPriority() const override;

    bool OnBeforeMoveEffect(Dealer &, const Actor &, const Location &) const override;
};

unsigned
BlazeCard::GetPriority() const
{
    return 2;
}

bool
BlazeCard::OnBeforeMoveEffect(Dealer &, const Actor &, const Location &) const
{
    // const auto & field = dealer.GetContent().GetField();
    for (size_t row = 0; row < Field::row; ++row) {
        for (size_t col = 0; col < Field::col; ++col) {
            // XXX field.Peek(row, col).SetBlaze();
        }
    }
    return false;
}

} // namespace

std::unique_ptr<Card>
Blaze()
{
    return std::make_unique<BlazeCard>();
}

} // namespace card
} // namesapce cylvionpp
