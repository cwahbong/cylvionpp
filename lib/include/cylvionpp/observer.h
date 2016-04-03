#ifndef CYLVIONPP_OBSERVER_H
#define CYLVIONPP_OBSERVER_H

#include "cylvionpp_export.h"

#include <memory>

namespace cylvionpp {

class Operation;

class CYLVIONPP_EXPORT Observer {
public:
    virtual ~Observer() = 0;

    virtual void BeforeOperation(const Operation &) = 0;
    virtual void AfterOperation(const Operation &) = 0;
};

} // namespace cylvionpp

#endif // CYLVIONPP_OBSERVER_H
