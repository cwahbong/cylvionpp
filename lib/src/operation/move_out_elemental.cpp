#include "cylvionpp/operation.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/field.h"

namespace cylvionpp {
namespace operation {

namespace {

class MoveOutElementalOperation: public Operation {
public:
    MoveOutElementalOperation(const Location & location);

    std::string GetName() const override { return ""; }
    std::string GetDescription() const override { return ""; }

    bool Run(Content &) override;

private:
    Location _location;
};

MoveOutElementalOperation::MoveOutElementalOperation(const Location & location):
    _location(location)
{/* Empty. */}

bool
MoveOutElementalOperation::Run(Content & content)
{
    auto & field = content.GetField();
    const auto & card = field.Peek(_location);
    if (!card.IsRavage()) {
        throw std::logic_error("not an elemental");
    }
    if (card.GetStrength() > content.GetEdge()) {
        return false;
    }
    content.DecreaseEdge(card.GetStrength());
    field.Remove(_location);
    return true;
}

} // namespace

std::unique_ptr<Operation>
MoveOutElemental(const Location & location)
{
    return std::make_unique<MoveOutElementalOperation>(location);
}

} // namespace operation
} // namespace cylvionpp
