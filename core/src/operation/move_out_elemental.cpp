#include "cylvionpp/operation.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/field.h"

namespace cylvionpp {
namespace core {
namespace operation {

namespace {

class MoveOutElementalOperation: public Operation {
public:
    MoveOutElementalOperation(size_t row, size_t col);

    std::string GetName() const override { return ""; }
    std::string GetDescription() const override { return ""; }

    bool Run(Content &) override;

private:
    size_t _row;
    size_t _col;
};

MoveOutElementalOperation::MoveOutElementalOperation(size_t row, size_t col):
    _row(row),
    _col(col)
{/* Empty. */}

bool
MoveOutElementalOperation::Run(Content & content)
{
    auto & field = content.GetField();
    const auto & card = field.Peek(_row, _col);
    if (!card.IsRavage()) {
        throw std::logic_error("not an elemental");
    }
    if (card.GetStrength() > content.GetEdge()) {
        return false;
    }
    content.DecreaseEdge(card.GetStrength());
    field.Remove(_row, _col);
    return true;
}

} // namespace

std::unique_ptr<Operation>
MoveOutElemental(size_t row, size_t col)
{
    return std::make_unique<MoveOutElementalOperation>(row, col);
}

} // namespace operation
} // namespace core
} // namespace cylvionpp
