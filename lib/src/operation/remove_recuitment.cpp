#include "cylvionpp/operation.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/stack.h"

#include <sstream>

namespace cylvionpp {
namespace operation {

namespace {

class RemoveRecuitmentOperation: public Operation {
public:
    RemoveRecuitmentOperation(Index col);

    std::string GetName() const override;
    std::string GetDescription() const override;

    bool Run(Content &) override;

private:
    Index _col;
};

RemoveRecuitmentOperation::RemoveRecuitmentOperation(Index col):
    _col(col)
{/* Empty. */}

std::string
RemoveRecuitmentOperation::GetName() const
{
    return "remove recuitment";
}

std::string
RemoveRecuitmentOperation::GetDescription() const
{
    std::ostringstream oss;
    oss << _col << "-th col recuitment is cleared";
    return oss.str();
}

bool
RemoveRecuitmentOperation::Run(Content & content)
{
    auto & recuitment = content.GetRecuitment(_col);
    while (!recuitment.Empty()) {
        recuitment.Pop();
    }
    return true;
}

} // namespace

std::unique_ptr<Operation>
RemoveRecuitment(Index col)
{
    return std::make_unique<RemoveRecuitmentOperation>(col);
}

} // namespace operation
} // namespace cylvionpp
