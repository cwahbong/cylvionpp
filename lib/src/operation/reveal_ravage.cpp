#include "cylvionpp/operation.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/field.h"
#include "cylvionpp/stack.h"

#include <sstream>

namespace cylvionpp {
namespace operation {

namespace {

class RevealRavageOperation: public Operation {
public:
    RevealRavageOperation(Index row);
    std::string GetName() const override;
    std::string GetDescription() const override;

    bool Run(Content &) override;

private:
    Index _row;
};

RevealRavageOperation::RevealRavageOperation(Index row):
    _row(row)
{/* Empty. */}

std::string
RevealRavageOperation::GetName() const
{
    return "reveal ravage";
}

std::string
RevealRavageOperation::GetDescription() const
{
    std::ostringstream oss;
    oss << _row << "-th row ravage revealed";
    return oss.str();
}

bool
RevealRavageOperation::Run(Content & content)
{
    auto & field = content.GetField();
    field.Put({_row, Field::col - 1}, field.GetRavageStack(_row).Pop());
    return true;
}

} // namespace

std::unique_ptr<Operation>
RevealRavage(Index row)
{
    return std::make_unique<RevealRavageOperation>(row);
}

} // namespace operation
} // namespace cylvionpp
