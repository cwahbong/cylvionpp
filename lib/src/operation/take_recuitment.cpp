#include "cylvionpp/operation.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/stack.h"

#include <sstream>

namespace cylvionpp {
namespace operation {

namespace {

class TakeRecuitmentOperation: public Operation {
public:
    TakeRecuitmentOperation(Index col);

    std::string GetName() const override;
    std::string GetDescription() const override;

    bool Run(Content &) override;

private:
    Index _col;
};

TakeRecuitmentOperation::TakeRecuitmentOperation(Index col):
    _col(col)
{/* Empty. */}

std::string
TakeRecuitmentOperation::GetName() const
{
    return "take recuitment";
}

std::string
TakeRecuitmentOperation::GetDescription() const
{
    std::ostringstream oss;
    oss << _col << "-th col recuitment is taked";
    return oss.str();
}

bool
TakeRecuitmentOperation::Run(Content & content)
{
    auto & recuitment = content.GetRecuitment(_col);
    while (!recuitment.Empty()) {
        content.GetUndrawn().Push(recuitment.Pop());
    }
    return true;
}

} // namespace

std::unique_ptr<Operation>
TakeRecuitment(Index col)
{
    return std::make_unique<TakeRecuitmentOperation>(col);
}

} // namespace operation
} // namespace cylvionpp
