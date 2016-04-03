#include "cylvionpp/operation.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/field.h"
#include "cylvionpp/hand.h"

namespace cylvionpp {
namespace operation {

namespace {

class PutCylvanOperation: public Operation {
public:
    PutCylvanOperation(Index idx, const Location & location);

    std::string GetName() const override { return ""; }
    std::string GetDescription() const override { return ""; }

    bool Run(Content &) override;

private:
    Index _idx;
    Location _location;
};

PutCylvanOperation::PutCylvanOperation(Index idx, const Location & location):
    _idx(idx),
    _location(location)
{/* Empty. */}

bool
PutCylvanOperation::Run(Content & content)
{
    auto card = content.GetHand().Remove(_idx);
    if (!content.GetField().Put(_location, std::move(card))) {
        // TODO error handling
    }
    return true;
}

} // namespace

std::unique_ptr<Operation>
PutCylvan(Index idx, const Location & location)
{
    return std::make_unique<PutCylvanOperation>(idx, location);
}

} // namespace operation
} // namespace cylvionpp
