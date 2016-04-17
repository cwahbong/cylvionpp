#include "defense_animal.h"

#include "cylvionpp/content.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/field.h"
#include "cylvionpp/operation.h"

#include <algorithm>

namespace cylvionpp {
namespace card {

namespace {

size_t
CountTree(const Field & field)
{
    size_t res = 0;
    for (Index r = 0; r < Field::row; ++r) {
        for (Index c = 0; c < Field::col; ++c) {
            res += field.Peek({r, c}).IsTree();
        }
    }
    return res;
}

class StagCard: public DefenseAnimalCard {
public:
    StagCard();

    std::string GetName() const override;

private:
    bool OnUseEffect(Dealer & dealer, const Actor &, Index) const override;
};

StagCard::StagCard():
    DefenseAnimalCard(0)
{/* Empty. */}

std::string
StagCard::GetName() const
{
    return "stag";
}

bool
StagCard::OnUseEffect(Dealer & dealer, const Actor &, Index) const
{
    const auto & content = dealer.GetContent();
    const auto & field = content.GetField();
    const auto amount = std::max<size_t>(2, CountTree(field));
    const auto boundedAmount = std::min<size_t>(12 - content.GetEdge(), amount);
    return dealer.Perform(*operation::IncreaseEdge(boundedAmount));
}

} // namespace

std::unique_ptr<Card>
Stag()
{
    return std::make_unique<StagCard>();
}

} // namespace card
} // namespace cylvionpp
