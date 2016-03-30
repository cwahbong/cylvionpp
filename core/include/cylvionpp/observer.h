#ifndef CYLVIONPP_OBSERVER_H
#define CYLVIONPP_OBSERVER_H

#include <memory>

namespace cylvionpp {
namespace core {

class EventReceiver {
public:
    virtual ~EventReceiver() = 0;

    virtual void BeforeEvent(const Event &) = 0;
    virtual void AfterEvent(const Event &) = 0;
};

} // namespace core
} // namespace cylvionpp

#endif // CYLVIONPP_OBSERVER_H
