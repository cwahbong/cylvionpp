#include "cylvionpp/dealer_helper.h"

#include "cylvionpp/card.h"
#include "cylvionpp/content.h"
#include "cylvionpp/dealer.h"
#include "cylvionpp/field.h"
#include "cylvionpp/operation.h"
#include "cylvionpp/operation_factory.h"

namespace cylvionpp {
namespace core {

bool
MoveLeftAllElementals(Dealer & dealer)
{
    const auto & field = dealer.GetContent().GetField();
    auto & operationFactory = dealer.GetOperationFactory();
    for (size_t row = 0; row < Field::row; ++row) {
        for (size_t col = 0; col < Field::col; ++col) {
            const auto & card = field.Peek(row, col);
            if (!card.IsRavage()) {
                continue;
            }
            if (col == 0) {
                dealer.Perform(*operationFactory.MoveOutElemental(row, col));
            } else {
                dealer.Perform(*operationFactory.MoveElemental(row, col, row, col - 1));
            }
        }
    }
    return true;
}

} // namespace core
} // namespace cylvionpp
