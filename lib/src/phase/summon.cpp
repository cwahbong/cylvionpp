#include "summon.h"

#include "cylvionpp/content.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/operation.h"
#include "cylvionpp/stack.h"

namespace cylvionpp {

std::unique_ptr<Phase>
SummonPhase::Action(Dealer & dealer, const Actor &)
{
    auto & content = dealer.GetContent();
    for (Index col = 0; col < 4; ++col) {
        if (content.GetSylvan().Empty()) {
            break;
        }
        if (content.GetRecuitment(col).Size() < 4) {
            dealer.Perform(*operation::SummonRecuitment(col));
        }
    }
    return NextPhase();
}

} // namespace cylvionpp
