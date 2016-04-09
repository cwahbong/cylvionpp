#include "support.h"

#include "cylvionpp/dealer.h"
#include "cylvionpp/field.h"
#include "cylvionpp/operation.h"

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
BlazeCard::OnBeforeMoveEffect(Dealer & dealer, const Actor &, const Location &) const
{
    for (Index row = 0; row < Field::row; ++row) {
        for (Index col = 0; col < Field::col; ++col) {
            dealer.Perform(*operation::BlazeElemental({row, col}));
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
