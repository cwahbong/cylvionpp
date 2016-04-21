#include "cylvionpp/operation.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/field.h"
#include "cylvionpp/stack.h"

#include <sstream>

namespace cylvionpp {
namespace operation {

namespace {

class ReverseTop2RavageOperation: public Operation {
public:
    ReverseTop2RavageOperation(Index row);
    std::string GetName() const override;
    std::string GetDescription() const override;

    bool Run(Content &) override;

private:
    Index _row;
};

ReverseTop2RavageOperation::ReverseTop2RavageOperation(Index row):
    _row(row)
{/* Empty. */}

std::string
ReverseTop2RavageOperation::GetName() const
{
    return "reverse ravage";
}

std::string
ReverseTop2RavageOperation::GetDescription() const
{
    std::ostringstream oss;
    oss << _row << "-th row ravage reversed";
    return oss.str();
}

bool
ReverseTop2RavageOperation::Run(Content & content)
{
    auto & ravage = content.GetField().GetRavageStack(_row);
    auto top = ravage.Pop();
    auto top2 = ravage.Pop();
    ravage.Push(std::move(top));
    ravage.Push(std::move(top2));
    return true;
}

} // namespace

std::unique_ptr<Operation>
ReverseTop2Ravage(Index row)
{
    return std::make_unique<ReverseTop2RavageOperation>(row);
}

} // namespace operation
} // namespace cylvionpp
