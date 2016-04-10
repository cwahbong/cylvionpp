#include "defense_animal.h"

#include "cylvionpp/actor.h"
#include "cylvionpp/dealer_helper.h"

namespace cylvionpp {
namespace card {

namespace {

class WhaleCard: public DefenseAnimalCard {
public:
    WhaleCard();

    std::string GetName() const override;

private:
    bool OnUseEffect(Dealer & dealer, const Actor & actor, Index) const override;
};

WhaleCard::WhaleCard():
    DefenseAnimalCard(0)
{/* Empty. */}

std::string
WhaleCard::GetName() const
{
    return "whale";
}

bool
WhaleCard::OnUseEffect(Dealer & dealer, const Actor & actor, Index) const
{
    // TODO error handling
    const auto fromRow = actor.AnswerIndex("elem from row");
    const auto fromCol = actor.AnswerIndex("elem from col");
    const auto toRow = actor.AnswerIndex("elem to row");
    const auto toCol = actor.AnswerIndex("elem to col");
    return MoveElemental(dealer, {fromRow, fromCol}, {toRow, toCol});
}

} // namespace

std::unique_ptr<Card>
Whale()
{
    return std::make_unique<WhaleCard>();
}


} // namespace card
} // namespace cylvionpp
