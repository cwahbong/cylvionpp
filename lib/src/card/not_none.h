#ifndef CYLVIONPP_INTERNAL_NOT_NONE_H
#define CYLVIONPP_INTERNAL_NOT_NONE_H

#include "cylvionpp/card.h"

namespace cylvionpp {

class NotNoneCard: public Card {
    bool IsNone() const override;
};

} // namespace cylvionpp

#endif // CYLVIONPP_INTERNAL_NOT_NONE_H
