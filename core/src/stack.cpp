#include "cylvionpp/card.h"
#include "cylvionpp/stack.h"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <exception>
#include <vector>
#include <random>
#include <utility>

namespace cylvionpp {
namespace core {

namespace {

class StackImpl: public Stack {
public:
    bool Empty() const override;
    unsigned Size() const override;

    const std::unique_ptr<Card> & Peek() const override;
    void Push(std::unique_ptr<Card> &&) override;
    std::unique_ptr<Card> Pop() override;
    void Shuffle() override;

private:
    std::vector<std::unique_ptr<Card>> c;
};

bool
StackImpl::Empty() const
{
    return c.empty();
}

unsigned
StackImpl::Size() const
{
    return c.size();
}

const std::unique_ptr<Card> &
StackImpl::Peek() const
{
    return c.back();
}

void
StackImpl::Push(std::unique_ptr<Card> && card)
{
    if (!card) {
        throw std::invalid_argument("card");
    }
    return c.push_back(std::move(card));
}

std::unique_ptr<Card>
StackImpl::Pop()
{
    std::unique_ptr<Card> top = std::move(c.back());
    assert(top);
    c.pop_back();
    return top;
}

void
StackImpl::Shuffle()
{
    const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(c.begin(), c.end(), std::default_random_engine(seed));
}

} // namespace

std::unique_ptr<Stack>
New()
{
    return std::make_unique<StackImpl>();
}

} // namespace core
} // namespace cylvionpp
