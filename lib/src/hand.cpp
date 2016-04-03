#include "cylvionpp/hand.h"

#include <algorithm>

#include "cylvionpp/card.h"

namespace cylvionpp {

namespace {

class HandImpl: public Hand {
public:
    size_t Size() const override;

    const std::unique_ptr<Card> & Peek(Index idx) const override;
    void Add(std::unique_ptr<Card> && card) override;
    std::unique_ptr<Card> Remove(Index idx) override;

private:
    std::vector<std::unique_ptr<Card>> c;
};

size_t
HandImpl::Size() const
{
    return c.size();
}

const std::unique_ptr<Card> &
HandImpl::Peek(Index idx) const
{
    return c.at(idx);
}

void
HandImpl::Add(std::unique_ptr<Card> && card)
{
    c.push_back(std::move(card));
}

std::unique_ptr<Card>
HandImpl::Remove(Index idx)
{
    std::swap(c.at(idx), c.back());
    std::unique_ptr<Card> card = std::move(c.back());
    c.pop_back();
    return card;
}

} // namespace

Hand::~Hand()
{/* Empty. */}

std::unique_ptr<Hand>
Hand::New()
{
    return std::make_unique<HandImpl>();
}

} // namespace cylvionpp
