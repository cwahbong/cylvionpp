#include "cylvionpp/card.h"

#include <exception>

#include "cylvionpp/actor.h"
#include "cylvionpp/content.h"
#include "cylvionpp/field.h"

namespace cylvionpp {
namespace core {

namespace {

class None: public Card {
public:
    unsigned GetCost() const override { throw std::logic_error("None"); }
    unsigned GetStrength() const override { throw std::logic_error("None"); }
    unsigned GetVitality() const override { throw std::logic_error("None"); }

    bool IsCylvan() const override { return false; }
    bool IsRavage() const override { return false; }
    bool IsNone() const override { return true; }

private:
    bool OnBeforeMove(Content &, const Actor &, std::unique_ptr<Card> &&) override { throw std::logic_error("None"); }
    bool OnUse(Content &, const Actor &, std::unique_ptr<Card> &&) override { throw std::logic_error("None"); }
};

class NotNone: public Card {
    bool IsNone() const override { return false; }
};

} // namespace

std::unique_ptr<Card>
Card::NewNone()
{
    return std::make_unique<None>();
}

namespace {

class Cylvan: public NotNone {
public:
    Cylvan(unsigned cost): _cost(cost) {/* Empty. */}

    unsigned GetCost() const override { return _cost; }

    bool IsCylvan() const override { return true; }
    bool IsRavage() const override { return false; }

    bool OnBeforeMove(Content &, const Actor &, std::unique_ptr<Card> &&) override { return true; }
    bool OnUse(Content & content, const Actor & actor, std::unique_ptr<Card> &&) override;

private:
    virtual bool OnUseEffect(Content & content, const Actor & actor, std::unique_ptr<Card> &&) = 0;

    unsigned _cost;
};

bool
Cylvan::OnUse(Content & content, const Actor & actor, std::unique_ptr<Card> && transfer)
{
    if (content.GetMana() < GetCost()) {
        return false;
    }
    if (!OnUseEffect(content, actor, std::move(transfer))) {
        return false;
    }
    content.SetMana(content.GetMana() - GetCost());
    return true;
}

class OnFieldCylvan: public Cylvan {
public:
    OnFieldCylvan(unsigned cost): Cylvan(cost) {/* Empty. */}

    bool OnUseEffect(Content & content, const Actor & actor, std::unique_ptr<Card> && transfer) override;
};

bool
OnFieldCylvan::OnUseEffect(Content & content, const Actor & actor, std::unique_ptr<Card> && transfer)
{
    Field & field = content.GetField();
    size_t row = actor.AnswerIndex("put field row");
    size_t col = actor.AnswerIndex("put field col");
    return field.Put(row, col, std::move(transfer));
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

} // namespace

std::unique_ptr<Card>
Card::NewFountain(unsigned cost, unsigned strength)
{
    return std::make_unique<Fountain>(cost, strength);
}

std::unique_ptr<Card>
Card::NewTree(unsigned cost, unsigned vitality)
{
    return std::make_unique<Tree>(cost, vitality);
}

namespace {

class Ravage: public NotNone {
public:
    unsigned GetCost() const override { return 0; }
    unsigned GetVitality() const override { return 0; }

    bool IsCylvan() const override { return false; }
    bool IsRavage() const override { return true; }

    bool OnUse(Content &, const Actor &, std::unique_ptr<Card> &&) override { throw std::logic_error("Ravage is not usable"); }
};

class Elemental: public Ravage {
public:
    Elemental(bool enhanced, unsigned strength, unsigned enhancedStrength):
        _enhanced(enhanced), _strength(strength), _enhancedStrength(enhancedStrength)
        {/* Empty. */}
    unsigned GetStrength() const { return _enhanced ? _enhancedStrength : _strength; }

    bool OnBeforeMove(Content &, const Actor &, std::unique_ptr<Card> &&) { return true; }

private:
    bool _enhanced;
    unsigned _strength;
    unsigned _enhancedStrength;
};

} // namespace

Card::~Card()
{/* Empty. */}

bool
Card::OnBeforeMove(std::unique_ptr<Card> && card, Content & content, const Actor & actor)
{
    return card->OnBeforeMove(content, actor, std::move(card));
}

bool
Card::OnUse(std::unique_ptr<Card> && card, Content & content, const Actor & actor)
{
    return card->OnUse(content, actor, std::move(card));
}

std::unique_ptr<Card>
Card::NewElemental(unsigned strength, unsigned enhancedStrength)
{
    return std::make_unique<Elemental>(false, strength, enhancedStrength);
}

} // namespace core
} // namespace cylvionpp
