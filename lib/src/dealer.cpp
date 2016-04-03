#include "cylvionpp/dealer.h"

#include "cylvionpp/content.h"
#include "cylvionpp/observer.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {

namespace {

class DealerImpl: public Dealer {
public:
    DealerImpl(std::unique_ptr<Content>, std::shared_ptr<Observer> observer);

    const Content & GetContent() const override;

    bool Perform(Operation &) override;

private:
    std::unique_ptr<Content> _content;
    std::shared_ptr<Observer> _observer;
};

DealerImpl::DealerImpl(std::unique_ptr<Content> content, std::shared_ptr<Observer> observer):
    _content(std::move(content)),
    _observer(observer)
{/* Empty. */}

const Content &
DealerImpl::GetContent() const
{
    return *_content;
}

bool
DealerImpl::Perform(Operation & operation)
{
    _observer->BeforeOperation(operation);
    operation.Run(*_content);
    _observer->AfterOperation(operation);
    return true;
}

} // namespace

Dealer::~Dealer() = default;

std::unique_ptr<Dealer>
Dealer::New(std::unique_ptr<Content> content, std::shared_ptr<Observer> observer)
{
    return std::make_unique<DealerImpl>(std::move(content), observer);
}

} // namespace cylvionpp
