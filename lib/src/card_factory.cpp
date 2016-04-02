#include "cylvionpp/card_factory.h"

#include "cylvionpp/actor.h"
#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/content_helper.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/field.h"
#include "cylvionpp/stack.h"
#include "cylvionpp/operation.h"


namespace cylvionpp {

namespace {

class None: public Card {
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

    bool OnBeforeMove(Dealer &, const Actor &, size_t, size_t) const override { throw std::logic_error("None"); }
    bool OnUseWhenReveal(Dealer &, const Actor &, size_t) const override { throw std::logic_error("None"); }
    bool OnUseWhenDefend(Dealer &, const Actor &, size_t) const override { throw std::logic_error("None"); }
};

class NotNone: public Card {
    bool IsNone() const override { return false; }
};

class Cylvan: public NotNone {
public:
    Cylvan(unsigned cost): _cost(cost) {/* Empty. */}

    unsigned GetCost() const override { return _cost; }
    unsigned GetPriority() const override { throw std::logic_error("cylvan has no priority"); }

    bool IsCylvan() const override { return true; }
    bool IsRavage() const override { return false; }
    bool IsBlazing() const override { return false; }

    void SetBlaze() override {/* Empty. */}

    bool OnBeforeMove(Dealer &, const Actor &, size_t, size_t) const override { return true; }
    bool OnUseWhenReveal(Dealer & content, const Actor & actor, size_t) const override;
    bool OnUseWhenDefend(Dealer & content, const Actor & actor, size_t) const override;

private:
    virtual bool CanUseWhenReveal() const = 0;
    virtual bool CanUseWhenDefend() const = 0;
    bool OnUse(Dealer & dealer, const Actor & actor, size_t) const;
    virtual bool OnUseEffect(Dealer & dealer, const Actor & actor, size_t) const = 0;

    unsigned _cost;
};

bool
Cylvan::OnUse(Dealer & dealer, const Actor & actor, size_t idx) const
{
    const auto & content = dealer.GetContent();
    if (content.GetMana() < GetCost()) {
        return false;
    }
    if (!OnUseEffect(dealer, actor, idx)) {
        return false;
    }
    // XXX content.SetMana(content.GetMana() - GetCost());
    // XXX move to discard pile
    return true;
}

bool
Cylvan::OnUseWhenReveal(Dealer & dealer, const Actor & actor, size_t idx) const
{
    if (!CanUseWhenReveal()) {
        return false;
    }
    return OnUse(dealer, actor, idx);
}

bool
Cylvan::OnUseWhenDefend(Dealer & dealer, const Actor & actor, size_t idx) const
{
    if (!CanUseWhenDefend()) {
        return false;
    }
    return OnUse(dealer, actor, idx);
}

class OnFieldCylvan: public Cylvan {
public:
    OnFieldCylvan(unsigned cost): Cylvan(cost) {/* Empty. */}

private:
    bool CanUseWhenReveal() const override { return false; }
    bool CanUseWhenDefend() const override { return true; }
    bool OnUseEffect(Dealer & dealer, const Actor & actor, size_t idx) const override;
};

bool
OnFieldCylvan::OnUseEffect(Dealer & dealer, const Actor & actor, size_t idx) const
{
    size_t row = actor.AnswerIndex("put field row");
    size_t col = actor.AnswerIndex("put field col");
    return dealer.Perform(*operation::PutCylvan(idx, row, col));
}

class Fountain: public OnFieldCylvan {
public:
    Fountain(unsigned cost, unsigned strength): OnFieldCylvan(cost), _strength(strength) {/* Empty. */}

    unsigned GetStrength() const override { return _strength; }
    unsigned GetVitality() const override { return 0; }

private:
    unsigned _strength;
};

class Tree: public OnFieldCylvan {
public:
    Tree(unsigned cost, unsigned vitality): OnFieldCylvan(cost), _vitality(vitality) {/* Empty. */}

    unsigned GetStrength() const override { return 0; }
    unsigned GetVitality() const override { return _vitality; }

private:
    unsigned _vitality;
};

class Animal: public Cylvan {
public:
    Animal(unsigned cost): Cylvan(cost) {/* Empty. */}

    unsigned GetStrength() const override { return 0; }
    unsigned GetVitality() const override { return 0; }
};

class DefenseAnimal: public Animal {
public:
    DefenseAnimal(unsigned cost): Animal(cost) {/* Empty. */}

private:
    bool CanUseWhenReveal() const override { return false; }
    bool CanUseWhenDefend() const override { return true; }
};

class Whale: public DefenseAnimal {
public:
    Whale(): DefenseAnimal(0) {/* Empty. */}

private:
    bool OnUseEffect(Dealer & dealer, const Actor & actor, size_t idx) const override;
};

bool
Whale::OnUseEffect(Dealer & dealer, const Actor & actor, size_t idx) const
{
    // TODO error handling
    size_t fromRow = actor.AnswerIndex("elem from row");
    size_t fromCol = actor.AnswerIndex("elem from col");
    size_t toRow = actor.AnswerIndex("elem to row");
    size_t toCol = actor.AnswerIndex("elem to col");
    return dealer.Perform(*operation::MoveElemental(fromRow, fromCol, toRow, toCol));
}

class Elephant: public DefenseAnimal {
public:
    Elephant(): DefenseAnimal(1) {/* Empty. */}

private:
    bool OnUseEffect(Dealer & dealer, const Actor & actor, size_t idx) const override;
};

bool
Elephant::OnUseEffect(Dealer & dealer, const Actor & actor, size_t idx) const
{
    size_t row = actor.AnswerIndex("elem row");
    size_t col = actor.AnswerIndex("elem col");
    const auto & field = dealer.GetContent().GetField();
    if (!field.Peek(row, col).IsNone()) {
        return false;
    }
    return dealer.Perform(*operation::RemoveFromField(row, col));
}

class Hedgehogs: public Animal {
public:
    Hedgehogs(): Animal(0) {/* Empty. */}

private:
    bool CanUseWhenReveal() const override { return true; }
    bool CanUseWhenDefend() const override { return false; }
    bool OnUseEffect(Dealer & dealer, const Actor & actor, size_t idx) const override;
};

bool
Hedgehogs::OnUseEffect(Dealer & dealer, const Actor & actor, size_t idx) const
{
    const size_t row = actor.AnswerIndex("elem row");
    const size_t col = Field::col - 1;
    const auto & field = dealer.GetContent().GetField();
    if (!field.Peek(row, col).IsRavage()) {
        return false;
    }
    return dealer.Perform(*operation::RemoveFromField(row, col));
}

class Owl: public DefenseAnimal {
public:
    Owl(): DefenseAnimal(1) {/* Empty. */}

private:
    bool OnUseEffect(Dealer & dealer, const Actor & actor, size_t idx) const override;
};

bool
Owl::OnUseEffect(Dealer & dealer, const Actor &, size_t idx) const
{
    return dealer.Perform(*operation::PlayerDraw(3));
}

class Ravage: public NotNone {
public:
    unsigned GetCost() const override { return 0; }
    unsigned GetVitality() const override { return 0; }

    bool IsCylvan() const override { return false; }
    bool IsRavage() const override { return true; }

    bool OnUseWhenReveal(Dealer &, const Actor &, size_t) const override { throw std::logic_error("Ravage is not usable"); }
    bool OnUseWhenDefend(Dealer &, const Actor &, size_t) const override { throw std::logic_error("Ravage is not usable"); }
};

class Elemental: public Ravage {
public:
    Elemental(bool enhanced, unsigned strength, unsigned enhancedStrength):
        _enhanced(enhanced), _strength(strength), _enhancedStrength(enhancedStrength)
        {/* Empty. */}
    unsigned GetStrength() const override { return _enhanced ? _enhancedStrength : _strength; }
    unsigned GetPriority() const override { return 4; }

    bool IsBlazing() const override { return _enhanced; }

    void SetBlaze() override { _enhanced = true; }

    bool OnBeforeMove(Dealer &, const Actor &, size_t, size_t) const override { return true; }

private:
    bool _enhanced;
    unsigned _strength;
    unsigned _enhancedStrength;
};

class Support: public Ravage {
    unsigned GetStrength() const override { throw std::logic_error("Support has no strength"); }

    bool IsBlazing() const override { return false; }

    void SetBlaze() override {/* Empty. */}

    bool OnBeforeMove(Dealer & dealer, const Actor & actor, size_t row, size_t col) const override final;

private:
    virtual bool OnBeforeMoveEffect(Dealer & dealer, const Actor & actor, size_t row, size_t col) const = 0;
};

bool
Support::OnBeforeMove(Dealer & dealer, const Actor & actor, size_t row, size_t col) const
{
    if (!OnBeforeMoveEffect(dealer, actor, row, col)) {
        return false;
    }
    return dealer.Perform(*operation::RemoveFromField(row, col));
}

class Blaze: public Support {
    unsigned GetPriority() const override { return 2; }

    bool OnBeforeMoveEffect(Dealer &, const Actor &, size_t, size_t) const override;
};

bool
Blaze::OnBeforeMoveEffect(Dealer & dealer, const Actor &, size_t, size_t) const
{
    const auto & field = dealer.GetContent().GetField();
    for (size_t row = 0; row < Field::row; ++row) {
        for (size_t col = 0; col < Field::col; ++col) {
            // XXX field.Peek(row, col).SetBlaze();
        }
    }
    return false;
}

class Simoon: public Support {
    unsigned GetPriority() const override { return 3; }

    bool OnBeforeMoveEffect(Dealer &, const Actor &, size_t, size_t) const override;
};

bool
Simoon::OnBeforeMoveEffect(Dealer & dealer, const Actor &, size_t, size_t) const
{
    MoveLeftAllElementals(dealer);
    return false;
}

class CardFactoryImpl: public CardFactory {
public:
    std::unique_ptr<Card> NewNone() override;
    std::unique_ptr<Card> NewFountain(unsigned cost, unsigned strength) override;
    std::unique_ptr<Card> NewTree(unsigned cost, unsigned vitality) override;
    std::unique_ptr<Card> NewWhale() override;
    std::unique_ptr<Card> NewElephant() override;
    std::unique_ptr<Card> NewHedgehogs() override;
    std::unique_ptr<Card> NewOwl() override;
    std::unique_ptr<Card> NewElemental(unsigned strength, unsigned enhancedStrength) override;
    std::unique_ptr<Card> NewBlaze() override;
    std::unique_ptr<Card> NewSimoon() override;
};

std::unique_ptr<Card>
CardFactoryImpl::NewNone()
{
    return std::make_unique<None>();
}

std::unique_ptr<Card>
CardFactoryImpl::NewFountain(unsigned cost, unsigned strength)
{
    return std::make_unique<Fountain>(cost, strength);
}

std::unique_ptr<Card>
CardFactoryImpl::NewTree(unsigned cost, unsigned vitality)
{
    return std::make_unique<Tree>(cost, vitality);
}

std::unique_ptr<Card>
CardFactoryImpl::NewWhale()
{
    return std::make_unique<Whale>();
}

std::unique_ptr<Card>
CardFactoryImpl::NewElephant()
{
    return std::make_unique<Elephant>();
}

std::unique_ptr<Card>
CardFactoryImpl::NewHedgehogs()
{
    return std::make_unique<Hedgehogs>();
}

std::unique_ptr<Card>
CardFactoryImpl::NewOwl()
{
    return std::make_unique<Owl>();
}

std::unique_ptr<Card>
CardFactoryImpl::NewElemental(unsigned strength, unsigned enhancedStrength)
{
    return std::make_unique<Elemental>(false, strength, enhancedStrength);
}

std::unique_ptr<Card>
CardFactoryImpl::NewBlaze()
{
    return std::make_unique<Blaze>();
}

std::unique_ptr<Card>
CardFactoryImpl::NewSimoon()
{
    return std::make_unique<Simoon>();
}

} // namespace

std::unique_ptr<CardFactory>
NewCardFactory()
{
    return std::make_unique<CardFactoryImpl>();
}

} // namespace cylvionpp
