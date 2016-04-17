#include "cylvionpp/operation.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/stack.h"

#include <sstream>

namespace cylvionpp {
namespace operation {

namespace {

class SummonRecuitmentOperation: public Operation {
public:
    SummonRecuitmentOperation(Index col);

    std::string GetName() const override;
    std::string GetDescription() const override;

    bool Run(Content &) override;

private:
    Index _col;
};

SummonRecuitmentOperation::SummonRecuitmentOperation(Index col):
    _col(col)
{/* Empty. */}

std::string
SummonRecuitmentOperation::GetName() const
{
    return "summon recuitment";
}

std::string
SummonRecuitmentOperation::GetDescription() const
{
    std::ostringstream oss;
    oss << _col << "-th col is summoned";
    return oss.str();
}

bool
SummonRecuitmentOperation::Run(Content & content)
{
    auto & sylvan = content.GetSylvan();
    if (sylvan.Empty()) {
        throw std::logic_error("empty sylvan");
    }
    content.GetRecuitment(_col).Push(sylvan.Pop());
    return true;
}

} // namespace

std::unique_ptr<Operation>
SummonRecuitment(Index col)
{
    return std::make_unique<SummonRecuitmentOperation>(col);
}

} // namespace operation
} // namespace cylvionpp
