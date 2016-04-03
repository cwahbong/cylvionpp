#ifndef CYLVIONPP_TYPES_H
#define CYLVIONPP_TYPES_H

#include "cylvionpp_export.h"

#include <cstdint>
#include <ostream>

namespace cylvionpp {

using Index = int_fast16_t;

struct CYLVIONPP_EXPORT Location {
    Index row;
    Index col;
};

CYLVIONPP_EXPORT std::ostream & operator<<(std::ostream & os, const Location & location);

} // namespace cylvionpp

#endif // CYLVIONPP_TYPE_H
