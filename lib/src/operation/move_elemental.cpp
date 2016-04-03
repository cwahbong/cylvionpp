#include "cylvionpp/operation.h"

#include "cylvionpp/content.h"
#include "cylvionpp/field.h"

#include <sstream>

namespace cylvionpp {
namespace operation {

namespace {

class MoveElementalOperation: public Operation {
public:
    MoveElementalOperation(const Location & from, const Location & to);

    std::string GetName() const override;
    std::string GetDescription() const override;

    bool Run(Content &) override;

private:
    Location _from;
    Location _to;
};

MoveElementalOperation::MoveElementalOperation(const Location & from, const Location & to):
    _from(from),
    _to(to)
{/* Empty. */}

std::string
MoveElementalOperation::GetName() const
{
    return "move elemental";
}

std::string
MoveElementalOperation::GetDescription() const
{
    std::ostringstream oss;
    oss << "elemental moved from " << _from << " to " << _to;
    return oss.str();
}

bool
MoveElementalOperation::Run(Content & content)
{
    content.GetField().Move(_from, _to);
    // TODO error handling
    return true;
}

} // namespace

std::unique_ptr<Operation>
MoveElemental(const Location & from, const Location & to)
{
    return std::make_unique<MoveElementalOperation>(from, to);
}

} // namespace operation
} // namespace cylvionpp
