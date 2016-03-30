#include "cylvionpp/dealer.h"

#include "cylvionpp/content.h"
#include "cylvionpp/operation.h"
#include "cylvionpp/operation_factory.h"

namespace cylvionpp {
namespace core {

namespace {

class DealerImpl: public Dealer {
public:
    DealerImpl(std::unique_ptr<Content>, std::unique_ptr<OperationFactory>);

    const Content & GetContent() const override;

    bool Perform(Operation &) override;
    OperationFactory & GetOperationFactory() const override;

private:
    std::unique_ptr<Content> _content;
    std::unique_ptr<OperationFactory> _operationFactory;
};

DealerImpl::DealerImpl(std::unique_ptr<Content> content, std::unique_ptr<OperationFactory> operationFactory):
    _content(std::move(content)),
    _operationFactory(std::move(operationFactory))
{/* Empty. */}

const Content &
DealerImpl::GetContent() const
{
    return *_content;
}

bool
DealerImpl::Perform(Operation & operation)
{
    // Before
    operation.Run(*_content);
    // After
    // TODO return
    return true;
}

OperationFactory &
DealerImpl::GetOperationFactory() const
{
    return *_operationFactory;
}

} // namespace

Dealer::~Dealer() = default;

std::unique_ptr<Dealer>
Dealer::New(std::unique_ptr<Content> content, std::unique_ptr<OperationFactory> operationFactory)
{
    return std::make_unique<DealerImpl>(std::move(content), std::move(operationFactory));
}

} // namespace core
} // namespace cylvionpp
