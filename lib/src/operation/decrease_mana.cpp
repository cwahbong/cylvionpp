#include "cylvionpp/operation.h"

#include "cylvionpp/content.h"

#include <sstream>

namespace cylvionpp {
namespace operation {

namespace {

class DecreaseManaOperation: public Operation {
public:
    DecreaseManaOperation(size_t amount);

    std::string GetName() const override;
    std::string GetDescription() const override;

    bool Run(Content &) override;

private:
    size_t _amount;
};

DecreaseManaOperation::DecreaseManaOperation(size_t amount):
    _amount(amount)
{/* Empty. */}

std::string
DecreaseManaOperation::GetName() const
{
    return "decrease mana";
}

std::string
DecreaseManaOperation::GetDescription() const
{
    std::ostringstream oss;
    oss << _amount << " mana is decreased";
    return oss.str();
}

bool
DecreaseManaOperation::Run(Content & content)
{
    content.SetMana(content.GetMana() - _amount);
    return true;
}

} // namespace

std::unique_ptr<Operation>
DecreaseMana(size_t amount)
{
    return std::make_unique<DecreaseManaOperation>(amount);
}

} // namespace operation
} // namespace cylvionpp
