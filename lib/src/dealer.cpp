#include "cylvionpp/dealer.h"

#include "cylvionpp/content.h"
#include "cylvionpp/operation.h"

namespace cylvionpp {

namespace {

class DealerImpl: public Dealer {
public:
    DealerImpl(std::unique_ptr<Content>);

    const Content & GetContent() const override;

    bool Perform(Operation &) override;

private:
    std::unique_ptr<Content> _content;
};

DealerImpl::DealerImpl(std::unique_ptr<Content> content):
    _content(std::move(content))
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

} // namespace

Dealer::~Dealer() = default;

std::unique_ptr<Dealer>
Dealer::New(std::unique_ptr<Content> content)
{
    return std::make_unique<DealerImpl>(std::move(content));
}

} // namespace cylvionpp
