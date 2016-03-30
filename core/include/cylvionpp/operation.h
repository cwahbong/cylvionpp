#ifndef CYLVIONPP_OPERATION_H
#define CYLVIONPP_OPERATION_H

#include <string>

namespace cylvionpp {
namespace core {

class Content;

class Operation {
public:
    virtual ~Operation() = 0;

    virtual std::string GetName() const = 0;
    virtual std::string GetDescription() const = 0;

    virtual bool Run(Content &) = 0;
};

} // namespace core
} // namespace cylvionpp

#endif // CYLVIONPP_OPERATION_H
