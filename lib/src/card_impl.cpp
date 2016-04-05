#include "cylvionpp/actor.h"
#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/content_helper.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/dealer_helper.h"
#include "cylvionpp/field.h"
#include "cylvionpp/stack.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {

namespace {

class NoneCard: public Card {
public:
    unsigned GetCost() const override { throw std::logic_error("None"); }
    unsigned GetStrength() const override { throw std::logic_error("None"); }
    unsigned GetVitality() const override { throw std::logic_error("None"); }
    unsigned GetPriority() const override { throw std::logic_error("None"); }

    bool IsCylvan() const override { return false; }
    bool IsRavage() const override { return false; }
    bool IsBlazing() const override { return false; }
    bool IsNone() const override { return true; }

    void SetBlaze() override { throw std::logic_error("None"); }

    bool OnBeforeMove(Dealer &, const Actor &, const Location &) const override { throw std::logic_error("None"); }
    bool OnUseWhenReveal(Dealer &, const Actor &, Index) const override { throw std::logic_error("None"); }
    bool OnUseWhenDefend(Dealer &, const Actor &, Index) const override { throw std::logic_error("None"); }
};

class NotNoneCard: public Card {
    bool IsNone() const override { return false; }
};

class CylvanCard: public NotNoneCard {
public:
    CylvanCard(unsigned cost): _cost(cost) {/* Empty. */}

    unsigned GetCost() const override { return _cost; }
    unsigned GetPriority() const override { throw std::logic_error("cylvan has no priority"); }

    bool IsCylvan() const override { return true; }
    bool IsRavage() const override { return false; }
    bool IsBlazing() const override { return false; }

    void SetBlaze() override {/* Empty. */}

    bool OnBeforeMove(Dealer &, const Actor &, const Location &) const override { return true; }
    bool OnUseWhenReveal(Dealer & content, const Actor & actor, Index) const override;
    bool OnUseWhenDefend(Dealer & content, const Actor & actor, Index) const override;

private:
    virtual bool CanUseWhenReveal() const = 0;
    virtual bool CanUseWhenDefend() const = 0;
    bool OnUse(Dealer & dealer, const Actor & actor, Index) const;
    virtual bool OnUseEffect(Dealer & dealer, const Actor & actor, Index) const = 0;

    unsigned _cost;
};

bool
CylvanCard::OnUse(Dealer & dealer, const Actor & actor, Index idx) const
{
    const auto & content = dealer.GetContent();
    if (content.GetMana() < GetCost()) {
        return false;
    }
    if (!OnUseEffect(dealer, actor, idx)) {
        return false;
    }
    dealer.Perform(*operation::DecreaseMana(GetCost()));
    return true;
}

bool
CylvanCard::OnUseWhenReveal(Dealer & dealer, const Actor & actor, Index idx) const
{
    if (!CanUseWhenReveal()) {
        return false;
    }
    return OnUse(dealer, actor, idx);
}

bool
CylvanCard::OnUseWhenDefend(Dealer & dealer, const Actor & actor, Index idx) const
{
    if (!CanUseWhenDefend()) {
        return false;
    }
    return OnUse(dealer, actor, idx);
}

class OnFieldCylvanCard: public CylvanCard {
public:
    OnFieldCylvanCard(unsigned cost): CylvanCard(cost) {/* Empty. */}

private:
    bool CanUseWhenReveal() const override { return false; }
    bool CanUseWhenDefend() const override { return true; }
    bool OnUseEffect(Dealer & dealer, const Actor & actor, Index idx) const override;
};

bool
OnFieldCylvanCard::OnUseEffect(Dealer & dealer, const Actor & actor, Index idx) const
{
    auto row = actor.AnswerIndex("put field row");
    auto col = actor.AnswerIndex("put field col");
    // TODO check before put
    return dealer.Perform(*operation::PutCylvan(idx, {row, col}));
}

class FountainCard: public OnFieldCylvanCard {
public:
    FountainCard(unsigned cost, unsigned strength): OnFieldCylvanCard(cost), _strength(strength) {/* Empty. */}

    unsigned GetStrength() const override { return _strength; }
    unsigned GetVitality() const override { return 0; }

private:
    unsigned _strength;
};

class TreeCard: public OnFieldCylvanCard {
public:
    TreeCard(unsigned cost, unsigned vitality): OnFieldCylvanCard(cost), _vitality(vitality) {/* Empty. */}

    unsigned GetStrength() const override { return 0; }
    unsigned GetVitality() const override { return _vitality; }

private:
    unsigned _vitality;
};

class AnimalCard: public CylvanCard {
public:
    AnimalCard(unsigned cost): CylvanCard(cost) {/* Empty. */}

    unsigned GetStrength() const override { return 0; }
    unsigned GetVitality() const override { return 0; }
};

class DefenseAnimalCard: public AnimalCard {
public:
    DefenseAnimalCard(unsigned cost): AnimalCard(cost) {/* Empty. */}

private:
    bool CanUseWhenReveal() const override { return false; }
    bool CanUseWhenDefend() const override { return true; }
};

class WhaleCard: public DefenseAnimalCard {
public:
    WhaleCard(): DefenseAnimalCard(0) {/* Empty. */}

private:
    bool OnUseEffect(Dealer & dealer, const Actor & actor, Index) const override;
};

bool
WhaleCard::OnUseEffect(Dealer & dealer, const Actor & actor, Index) const
{
    // TODO error handling
    const auto fromRow = actor.AnswerIndex("elem from row");
    const auto fromCol = actor.AnswerIndex("elem from col");
    const auto toRow = actor.AnswerIndex("elem to row");
    const auto toCol = actor.AnswerIndex("elem to col");
    return dealer.Perform(*operation::MoveElemental({fromRow, fromCol}, {toRow, toCol}));
}

class ElephantCard: public DefenseAnimalCard {
public:
    ElephantCard(): DefenseAnimalCard(1) {/* Empty. */}

private:
    bool OnUseEffect(Dealer & dealer, const Actor & actor, Index) const override;
};

bool
ElephantCard::OnUseEffect(Dealer & dealer, const Actor & actor, Index) const
{
    const auto row = actor.AnswerIndex("elem row");
    const auto col = actor.AnswerIndex("elem col");
    const auto & field = dealer.GetContent().GetField();
    if (!field.Peek({row, col}).IsNone()) {
        return false;
    }
    return dealer.Perform(*operation::RemoveFromField({row, col}));
}

class HedgehogsCard: public AnimalCard {
public:
    HedgehogsCard(): AnimalCard(0) {/* Empty. */}

private:
    bool CanUseWhenReveal() const override { return true; }
    bool CanUseWhenDefend() const override { return false; }
    bool OnUseEffect(Dealer & dealer, const Actor & actor, Index) const override;
};

bool
HedgehogsCard::OnUseEffect(Dealer & dealer, const Actor & actor, Index) const
{
    const auto row = actor.AnswerIndex("elem row");
    const auto col = Field::col - 1;
    const auto & field = dealer.GetContent().GetField();
    if (!field.Peek({row, col}).IsRavage()) {
        return false;
    }
    return dealer.Perform(*operation::RemoveFromField({row, col}));
}

class OwlCard: public DefenseAnimalCard {
public:
    OwlCard(): DefenseAnimalCard(1) {/* Empty. */}

private:
    bool OnUseEffect(Dealer & dealer, const Actor &, Index) const override;
};

bool
OwlCard::OnUseEffect(Dealer & dealer, const Actor &, Index) const
{
    return dealer.Perform(*operation::PlayerDraw(3));
}

class RavageCard: public NotNoneCard {
public:
    unsigned GetCost() const override { return 0; }
    unsigned GetVitality() const override { return 0; }

    bool IsCylvan() const override { return false; }
    bool IsRavage() const override { return true; }

    bool OnUseWhenReveal(Dealer &, const Actor &, Index) const override { throw std::logic_error("Ravage is not usable"); }
    bool OnUseWhenDefend(Dealer &, const Actor &, Index) const override { throw std::logic_error("Ravage is not usable"); }
};

class ElementalCard: public RavageCard {
public:
    ElementalCard(bool enhanced, unsigned strength, unsigned enhancedStrength):
        _enhanced(enhanced), _strength(strength), _enhancedStrength(enhancedStrength)
        {/* Empty. */}
    unsigned GetStrength() const override { return _enhanced ? _enhancedStrength : _strength; }
    unsigned GetPriority() const override { return 4; }

    bool IsBlazing() const override { return _enhanced; }

    void SetBlaze() override { _enhanced = true; }

    bool OnBeforeMove(Dealer &, const Actor &, const Location &) const override { return true; }

private:
    bool _enhanced;
    unsigned _strength;
    unsigned _enhancedStrength;
};

class SupportCard: public RavageCard {
    unsigned GetStrength() const override { throw std::logic_error("Support has no strength"); }

    bool IsBlazing() const override { return false; }

    void SetBlaze() override {/* Empty. */}

    bool OnBeforeMove(Dealer & dealer, const Actor & actor, const Location & location) const override final;

private:
    virtual bool OnBeforeMoveEffect(Dealer & dealer, const Actor & actor, const Location & location) const = 0;
};

bool
SupportCard::OnBeforeMove(Dealer & dealer, const Actor & actor, const Location & location) const
{
    if (!OnBeforeMoveEffect(dealer, actor, location)) {
        return false;
    }
    return dealer.Perform(*operation::RemoveFromField(location));
}

class BlazeCard: public SupportCard {
    unsigned GetPriority() const override { return 2; }

    bool OnBeforeMoveEffect(Dealer &, const Actor &, const Location &) const override;
};

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

class SimoonCard: public SupportCard {
    unsigned GetPriority() const override { return 3; }

    bool OnBeforeMoveEffect(Dealer &, const Actor &, const Location &) const override;
};

bool
SimoonCard::OnBeforeMoveEffect(Dealer & dealer, const Actor &, const Location &) const
{
    MoveLeftAllElementals(dealer);
    return false;
}

} // namespace

namespace card {

std::unique_ptr<Card>
None()
{
    return std::make_unique<NoneCard>();
}

std::unique_ptr<Card>
Fountain(unsigned cost, unsigned strength)
{
    return std::make_unique<FountainCard>(cost, strength);
}

std::unique_ptr<Card>
Tree(unsigned cost, unsigned vitality)
{
    return std::make_unique<TreeCard>(cost, vitality);
}

std::unique_ptr<Card>
Whale()
{
    return std::make_unique<WhaleCard>();
}

std::unique_ptr<Card>
Elephant()
{
    return std::make_unique<ElephantCard>();
}

std::unique_ptr<Card>
Hedgehogs()
{
    return std::make_unique<HedgehogsCard>();
}

std::unique_ptr<Card>
Owl()
{
    return std::make_unique<OwlCard>();
}

std::unique_ptr<Card>
Elemental(unsigned strength, unsigned enhancedStrength)
{
    return std::make_unique<ElementalCard>(false, strength, enhancedStrength);
}

std::unique_ptr<Card>
Blaze()
{
    return std::make_unique<BlazeCard>();
}

std::unique_ptr<Card>
Simoon()
{
    return std::make_unique<SimoonCard>();
}

} // namespace card

} // namespace cylvionpp