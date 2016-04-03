#include "cylvionpp/operation.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/field.h"

namespace cylvionpp {
namespace operation {

namespace {

class RemoveFromFieldOperation: public Operation {
public:
    RemoveFromFieldOperation(const Location & location);

    std::string GetName() const override { return ""; }
    std::string GetDescription() const override { return ""; }

    bool Run(Content &) override;

private:
    Location _location;
};

RemoveFromFieldOperation::RemoveFromFieldOperation(const Location & location):
    _location(location)
{/* Empty. */}

bool
RemoveFromFieldOperation::Run(Content & content)
{
    content.GetField().Remove(_location);
    // TODO error handling
    return true;
}

} // namespace

std::unique_ptr<Operation>
RemoveFromField(const Location & location)
{
    return std::make_unique<RemoveFromFieldOperation>(location);
}

} // namespace operation
} // namespace cylvionpp
