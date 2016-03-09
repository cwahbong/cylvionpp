#include "cylvionpp/card.h"

#include <exception>

#include "cylvionpp/actor.h"
#include "cylvionpp/content.h"
#include "cylvionpp/content_helper.h"
#include "cylvionpp/field.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {
namespace core {

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

private:
    bool OnBeforeMove(Content &, const Actor &, std::unique_ptr<Card> &&) override { throw std::logic_error("None"); }
    bool OnUseWhenReveal(Content &, const Actor &, std::unique_ptr<Card> &&) override { throw std::logic_error("None"); }
    bool OnUseWhenDefend(Content &, const Actor &, std::unique_ptr<Card> &&) override { throw std::logic_error("None"); }
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
    unsigned GetPriority() const override { throw std::logic_error("cylvan has no priority"); }

    bool IsCylvan() const override { return true; }
    bool IsRavage() const override { return false; }
    bool IsBlazing() const override { return false; }

    void SetBlaze() override {/* Empty. */}

    bool OnBeforeMove(Content &, const Actor &, std::unique_ptr<Card> &&) override { return true; }
    bool OnUseWhenReveal(Content & content, const Actor & actor, std::unique_ptr<Card> &&) override;
    bool OnUseWhenDefend(Content & content, const Actor & actor, std::unique_ptr<Card> &&) override;

private:
    virtual bool CanUseWhenReveal() = 0;
    virtual bool CanUseWhenDefend() = 0;
    bool OnUse(Content & content, const Actor & actor, std::unique_ptr<Card> &&);
    virtual bool OnUseEffect(Content & content, const Actor & actor, std::unique_ptr<Card> &&) = 0;

    unsigned _cost;
};

bool
Cylvan::OnUse(Content & content, const Actor & actor, std::unique_ptr<Card> && self)
{
    if (content.GetMana() < GetCost()) {
        return false;
    }
    if (!OnUseEffect(content, actor, std::move(self))) {
        return false;
    }
    content.SetMana(content.GetMana() - GetCost());
    return true;
}

bool
Cylvan::OnUseWhenReveal(Content & content, const Actor & actor, std::unique_ptr<Card> && self)
{
    if (!CanUseWhenReveal()) {
        return false;
    }
    return OnUse(content, actor, std::move(self));
}

bool
Cylvan::OnUseWhenDefend(Content & content, const Actor & actor, std::unique_ptr<Card> && self)
{
    if (!CanUseWhenDefend()) {
        return false;
    }
    return OnUse(content, actor, std::move(self));
}

class OnFieldCylvan: public Cylvan {
public:
    OnFieldCylvan(unsigned cost): Cylvan(cost) {/* Empty. */}

private:
    bool CanUseWhenReveal() override { return false; }
    bool CanUseWhenDefend() override { return true; }
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
    bool CanUseWhenReveal() override { return false; }
    bool CanUseWhenDefend() override { return true; }
};

class Whale: public DefenseAnimal {
public:
    Whale(): DefenseAnimal(0) {/* Empty. */}

private:
    bool OnUseEffect(Content & content, const Actor & actor, std::unique_ptr<Card> &&) override;
};

bool
Whale::OnUseEffect(Content & content, const Actor & actor, std::unique_ptr<Card> && transfer)
{
    // TODO error handling
    size_t fromRow = actor.AnswerIndex("elem from row");
    size_t fromCol = actor.AnswerIndex("elem from col");
    size_t toRow = actor.AnswerIndex("elem to row");
    size_t toCol = actor.AnswerIndex("elem to col");
    MoveElemental(content.GetField(), fromRow, fromCol, toRow, toCol);
    content.GetDiscarded().Push(std::move(transfer));
    return true;
}

class Elephant: public DefenseAnimal {
public:
    Elephant(): DefenseAnimal(1) {/* Empty. */}

private:
    bool OnUseEffect(Content & content, const Actor & actor, std::unique_ptr<Card> &&) override;
};

bool
Elephant::OnUseEffect(Content & content, const Actor & actor, std::unique_ptr<Card> && transfer)
{
    size_t row = actor.AnswerIndex("elem row");
    size_t col = actor.AnswerIndex("elem col");
    auto & field = content.GetField();
    if (!field.Peek(row, col).IsNone()) {
        return false;
    }
    field.Remove(row, col);
    content.GetDiscarded().Push(std::move(transfer));
    return true;
}

class Hedgehogs: public Animal {
public:
    Hedgehogs(): Animal(0) {/* Empty. */}

private:
    bool CanUseWhenReveal() override { return true; }
    bool CanUseWhenDefend() override { return false; }
    bool OnUseEffect(Content & content, const Actor & actor, std::unique_ptr<Card> &&) override;
};

bool
Hedgehogs::OnUseEffect(Content & content, const Actor & actor, std::unique_ptr<Card> && transfer)
{
    const size_t row = actor.AnswerIndex("elem row");
    const size_t col = Field::col - 1;
    auto & field = content.GetField();
    if (!field.Peek(row, col).IsRavage()) {
        return false;
    }
    field.Remove(row, col);
    content.GetDiscarded().Push(std::move(transfer));
    return true;
}

class Owl: public DefenseAnimal {
public:
    Owl(): DefenseAnimal(1) {/* Empty. */}

private:
    bool OnUseEffect(Content & content, const Actor & actor, std::unique_ptr<Card> &&) override;
};

bool
Owl::OnUseEffect(Content & content, const Actor &, std::unique_ptr<Card> && transfer)
{
    for (int i = 0; i < 3; ++i) {
        PlayerDraw(content);
    }
    content.GetDiscarded().Push(std::move(transfer));
    return true;
}

} // namespace

std::unique_ptr<Card>
Card::NewWhale()
{
    return std::make_unique<Whale>();
}

std::unique_ptr<Card>
Card::NewElephant()
{
    return std::make_unique<Elephant>();
}

std::unique_ptr<Card>
Card::NewHedgehogs()
{
    return std::make_unique<Hedgehogs>();
}

std::unique_ptr<Card>
Card::NewOwl()
{
    return std::make_unique<Owl>();
}

namespace {

class Ravage: public NotNone {
public:
    unsigned GetCost() const override { return 0; }
    unsigned GetVitality() const override { return 0; }

    bool IsCylvan() const override { return false; }
    bool IsRavage() const override { return true; }

    bool OnUseWhenReveal(Content &, const Actor &, std::unique_ptr<Card> &&) override { throw std::logic_error("Ravage is not usable"); }
    bool OnUseWhenDefend(Content &, const Actor &, std::unique_ptr<Card> &&) override { throw std::logic_error("Ravage is not usable"); }
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

    bool OnBeforeMove(Content &, const Actor &, std::unique_ptr<Card> &&) override { return true; }

private:
    bool _enhanced;
    unsigned _strength;
    unsigned _enhancedStrength;
};

class Support: public Ravage {
    unsigned GetStrength() const override { throw std::logic_error("Support has no strength"); }

    bool IsBlazing() const override { return false; }

    void SetBlaze() override {/* Empty. */}
};

class Blaze: public Support {
    unsigned GetPriority() const override { return 2; }

    bool OnBeforeMove(Content &, const Actor &, std::unique_ptr<Card> &&) override;
};

bool
Blaze::OnBeforeMove(Content & content, const Actor &, std::unique_ptr<Card> && self)
{
    auto & field = content.GetField();
    for (size_t row = 0; row < Field::row; ++row) {
        for (size_t col = 0; col < Field::col; ++col) {
            field.Peek(row, col).SetBlaze();
        }
    }
    self.reset(); // put to discarded elemental instead
    return false;
}

class Simoon: public Support {
    unsigned GetPriority() const override { return 3; }

    bool OnBeforeMove(Content &, const Actor &, std::unique_ptr<Card> &&) override;
};

bool
Simoon::OnBeforeMove(Content & content, const Actor &, std::unique_ptr<Card> && self)
{
    MoveLeftAllElementals(content);
    self.reset(); // put to discarded elemental instead
    return false;
}

} // namespace

std::unique_ptr<Card>
Card::NewElemental(unsigned strength, unsigned enhancedStrength)
{
    return std::make_unique<Elemental>(false, strength, enhancedStrength);
}

std::unique_ptr<Card>
Card::NewBlaze()
{
    return std::make_unique<Blaze>();
}

std::unique_ptr<Card>
Card::NewSimoon()
{
    return std::make_unique<Simoon>();
}

Card::~Card()
{/* Empty. */}

bool
Card::OnBeforeMove(std::unique_ptr<Card> && card, Content & content, const Actor & actor)
{
    return card->OnBeforeMove(content, actor, std::move(card));
}

bool
Card::OnUseWhenReveal(std::unique_ptr<Card> && card, Content & content, const Actor & actor)
{
    return card->OnUseWhenReveal(content, actor, std::move(card));
}

bool
Card::OnUseWhenDefend(std::unique_ptr<Card> && card, Content & content, const Actor & actor)
{
    return card->OnUseWhenDefend(content, actor, std::move(card));
}

} // namespace core
} // namespace cylvionpp
