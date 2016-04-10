#ifndef CYLVIONPP_TEST_EMPTY_OBSERVER_H
#define CYLVIONPP_TEST_EMPTY_OBSERVER_H

#include <cylvionpp/observer.h>

class EmptyObserver: public cylvionpp::Observer {
public:
    void BeforeOperation(const cylvionpp::Operation &) override {}
    void AfterOperation(const cylvionpp::Operation &) override {}
};

#endif // CYLVIONPP_TEST_EMPTY_OBSERVER_H
