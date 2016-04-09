#include "cylvionpp/operation.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/field.h"

#include <sstream>

namespace cylvionpp {
namespace operation {

namespace {

class BlazeElementalOperation: public Operation {
public:
    BlazeElementalOperation(const Location & location);

    std::string GetName() const override;
    std::string GetDescription() const override;

    bool Run(Content &) override;

private:
    Location _location;
};

BlazeElementalOperation::BlazeElementalOperation(const Location & location):
    _location(location)
{/* Empty. */}

std::string
BlazeElementalOperation::GetName() const
{
    return "blaze elemental";
}

std::string
BlazeElementalOperation::GetDescription() const
{
    std::ostringstream oss;
    oss << "elemental at" << _location << " is blazed";
    return oss.str();
}

bool
BlazeElementalOperation::Run(Content & content)
{
    content.GetField().Peek(_location).SetBlaze();
    // TODO error handling
    return true;
}

} // namespace

std::unique_ptr<Operation>
BlazeElemental(const Location & location)
{
    return std::make_unique<BlazeElementalOperation>(location);
}

} // namespace operation
} // namespace cylvionpp
