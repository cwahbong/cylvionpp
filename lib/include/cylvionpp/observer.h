#ifndef CYLVIONPP_OBSERVER_H
#define CYLVIONPP_OBSERVER_H

#include "cylvionpp_export.h"

#include <memory>

namespace cylvionpp {

class CYLVIONPP_EXPORT EventReceiver {
public:
    virtual ~EventReceiver() = 0;

    virtual void BeforeEvent(const Event &) = 0;
    virtual void AfterEvent(const Event &) = 0;
};

} // namespace cylvionpp

#endif // CYLVIONPP_OBSERVER_H
