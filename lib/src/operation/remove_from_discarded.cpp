#include "cylvionpp/operation.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/hand.h"

#include <sstream>

namespace cylvionpp {
namespace operation {

namespace {

class RemoveFromDiscardedOperation: public Operation {
public:
    RemoveFromDiscardedOperation(Index idx);
    std::string GetName() const override;
    std::string GetDescription() const override;

    bool Run(Content &) override;

private:
    Index _idx;
};

RemoveFromDiscardedOperation::RemoveFromDiscardedOperation(Index idx):
    _idx(idx)
{/* Empty. */}

std::string
RemoveFromDiscardedOperation::GetName() const
{
    return "remove from discarded";
}

std::string
RemoveFromDiscardedOperation::GetDescription() const
{
    std::ostringstream oss;
    oss << _idx << "-th discarded card removed";
    return oss.str();
}

bool
RemoveFromDiscardedOperation::Run(Content & content)
{
    content.GetDiscarded().Remove(_idx);
    return true;
}

} // namespace

std::unique_ptr<Operation>
RemoveFromDiscarded(Index idx)
{
    return std::make_unique<RemoveFromDiscardedOperation>(idx);
}

} // namespace operation
} // namespace cylvionpp
