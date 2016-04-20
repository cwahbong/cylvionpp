#include "cylvionpp/operation.h"

#include "cylvionpp/content.h"

#include <sstream>

namespace cylvionpp {
namespace operation {

namespace {

class IncreaseManaOperation: public Operation {
public:
    IncreaseManaOperation(size_t amount);

    std::string GetName() const override;
    std::string GetDescription() const override;

    bool Run(Content &) override;

private:
    size_t _amount;
};

IncreaseManaOperation::IncreaseManaOperation(size_t amount):
    _amount(amount)
{/* Empty. */}

std::string
IncreaseManaOperation::GetName() const
{
    return "increase mana";
}

std::string
IncreaseManaOperation::GetDescription() const
{
    std::ostringstream oss;
    oss << _amount << " mana is increased";
    return oss.str();
}

bool
IncreaseManaOperation::Run(Content & content)
{
    content.SetMana(content.GetMana() + _amount);
    return true;
}

} // namespace

std::unique_ptr<Operation>
IncreaseMana(size_t amount)
{
    return std::make_unique<IncreaseManaOperation>(amount);
}

} // namespace operation
} // namespace cylvionpp
