#include "cylvionpp/operation.h"

#include "cylvionpp/content.h"

#include <algorithm>

namespace cylvionpp {
namespace operation {

namespace {

class IncreaseEdgeOperation: public Operation {
public:
    IncreaseEdgeOperation(size_t amount);

    std::string GetName() const override { return ""; }
    std::string GetDescription() const override { return ""; }

    bool Run(Content &) override;

private:
    size_t _amount;
};

IncreaseEdgeOperation::IncreaseEdgeOperation(size_t amount):
    _amount(amount)
{/* Empty. */}

bool
IncreaseEdgeOperation::Run(Content & content)
{
    content.SetEdge(content.GetEdge() + _amount);
    return true;
}

} // namespace

std::unique_ptr<Operation>
IncreaseEdge(size_t amount)
{
    return std::make_unique<IncreaseEdgeOperation>(amount);
}

} // namespace operation
} // namespace cylvionpp
