#include "cylvionpp/operation.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/field.h"

#include <sstream>

namespace cylvionpp {
namespace operation {

namespace {

class MoveOutElementalOperation: public Operation {
public:
    MoveOutElementalOperation(const Location & location);

    std::string GetName() const override;
    std::string GetDescription() const override;

    bool Run(Content &) override;

private:
    Location _location;
};

MoveOutElementalOperation::MoveOutElementalOperation(const Location & location):
    _location(location)
{/* Empty. */}

std::string
MoveOutElementalOperation::GetName() const
{
    return "move out elemental";
}

std::string
MoveOutElementalOperation::GetDescription() const
{
    std::ostringstream oss;
    oss << "elemental moved out from " << _location;
    return oss.str();
}

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
