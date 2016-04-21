#include "cylvionpp/operation.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/field.h"
#include "cylvionpp/stack.h"

#include <sstream>

namespace cylvionpp {
namespace operation {

namespace {

class RemoveRavageOperation: public Operation {
public:
    RemoveRavageOperation(Index row);
    std::string GetName() const override;
    std::string GetDescription() const override;

    bool Run(Content &) override;

private:
    Index _row;
};

RemoveRavageOperation::RemoveRavageOperation(Index row):
    _row(row)
{/* Empty. */}

std::string
RemoveRavageOperation::GetName() const
{
    return "remove ravage";
}

std::string
RemoveRavageOperation::GetDescription() const
{
    std::ostringstream oss;
    oss << _row << "-th row ravage removed";
    return oss.str();
}

bool
RemoveRavageOperation::Run(Content & content)
{
    content.GetField().GetRavageStack(_row).Pop();
    return true;
}

} // namespace

std::unique_ptr<Operation>
RemoveRavage(Index row)
{
    return std::make_unique<RemoveRavageOperation>(row);
}

} // namespace operation
} // namespace cylvionpp
