#include "cylvionpp/desertions.h"

#include <algorithm>
#include <chrono>
#include <random>
#include <vector>
#include <utility>

namespace cylvionpp {

namespace {

class DesertionsImpl: public Desertions {
public:
    bool Empty() const override;
    unsigned Size() const override;

    Index Peek() const override;
    Index Peek(Index idx) const override;
    void Push(Index) override;
    Index Pop() override;
    void Shuffle() override;

private:
    std::vector<Index> c;
};

bool
DesertionsImpl::Empty() const
{
    return c.empty();
}

unsigned
DesertionsImpl::Size() const
{
    return c.size();
}

Index
DesertionsImpl::Peek() const
{
    return c.back();
}

Index
DesertionsImpl::Peek(Index idx) const
{
    return c[idx];
}

void
DesertionsImpl::Push(Index value)
{
    c.push_back(value);
}

Index
DesertionsImpl::Pop()
{
    Index value = c.back();
    c.pop_back();
    return value;
}

void
DesertionsImpl::Shuffle()
{
    const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(c.begin(), c.end(), std::default_random_engine(seed));
}

} // namespace

Desertions::~Desertions() = default;

std::unique_ptr<Desertions>
Desertions::New()
{
    return std::make_unique<DesertionsImpl>();
}

} // namespace cylvionpp
