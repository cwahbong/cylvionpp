#include "cylvionpp/operation_factory.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/hand.h"
#include "cylvionpp/operation.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {
namespace core {

namespace {

class PlayerDrawOperation: public Operation {
public:
    PlayerDrawOperation(size_t count);

    std::string GetName() const override {return ""; }
    std::string GetDescription() const override { return ""; }

    bool Run(Content &) override;

private:

    size_t _count;
};

PlayerDrawOperation::PlayerDrawOperation(size_t count):
    _count(count)
{/* Empty. */}

bool
PlayerDrawOperation::Run(Content & content)
{
    for (decltype(_count) i = 0; i < _count; ++i) {
        auto & undrawn = content.GetUndrawn();
        if (undrawn.Empty()) {
            auto & discarded = content.GetDiscarded();
            while (!discarded.Empty()) {
                undrawn.Push(discarded.Pop());
            }
            undrawn.Shuffle();
        }
        content.GetHand().Add(undrawn.Pop());
    }
    return true;
}

// TODO implement operations here

/* void
MoveOutElemental(Content & content, size_t fromRow, size_t fromCol)
{
    auto & field = content.GetField();
    const auto & card = field.Peek(fromRow, fromCol);
    if (!card.IsRavage()) {
        throw std::logic_error("not an elemental");
    }
    content.DecreaseEdge(card.GetStrength());
    field.Remove(fromRow, fromCol);
} */


class OperationFactoryImpl: public OperationFactory {
public:
    std::unique_ptr<Operation> PlayerDraw(size_t count) override;
    std::unique_ptr<Operation> MoveElemental(size_t fromRow, size_t fromCol, size_t toRow, size_t toCol) override;
    std::unique_ptr<Operation> MoveOutElemental(size_t row, size_t col) override;
};

std::unique_ptr<Operation>
OperationFactoryImpl::PlayerDraw(size_t count)
{
    return std::make_unique<PlayerDrawOperation>(count);
}

std::unique_ptr<Operation>
OperationFactoryImpl::MoveElemental(size_t fromRow, size_t fromCol, size_t toRow, size_t toCol)
{
    return nullptr;
}

std::unique_ptr<Operation>
OperationFactoryImpl::MoveOutElemental(size_t row, size_t col)
{
    return nullptr;
}

} // namespace

OperationFactory::~OperationFactory() = default;

std::unique_ptr<OperationFactory>
OperationFactory::New()
{
    return std::make_unique<OperationFactoryImpl>();
}

} // namespace core
} // namespace cylvionpp
