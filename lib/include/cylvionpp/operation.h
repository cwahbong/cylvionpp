#ifndef CYLVIONPP_OPERATION_H
#define CYLVIONPP_OPERATION_H

#include "cylvionpp_export.h"
#include "types.h"

#include <memory>
#include <string>

namespace cylvionpp {

class Content;

class CYLVIONPP_EXPORT Operation {
public:
    virtual ~Operation() = 0;

    virtual std::string GetName() const = 0;
    virtual std::string GetDescription() const = 0;

    virtual bool Run(Content &) = 0;
};

namespace operation {

CYLVIONPP_EXPORT std::unique_ptr<Operation> SummonRecuitment(Index col);
CYLVIONPP_EXPORT std::unique_ptr<Operation> PlayerDraw(size_t count);
CYLVIONPP_EXPORT std::unique_ptr<Operation> PlayerDiscardHand(Index idx);
CYLVIONPP_EXPORT std::unique_ptr<Operation> DecreaseMana(size_t amount);
CYLVIONPP_EXPORT std::unique_ptr<Operation> PutCylvan(Index idx, const Location & location);
CYLVIONPP_EXPORT std::unique_ptr<Operation> RevealRavage(Index row);
CYLVIONPP_EXPORT std::unique_ptr<Operation> MoveElemental(const Location & from, const Location & to);
CYLVIONPP_EXPORT std::unique_ptr<Operation> MoveOutElemental(const Location & location);
CYLVIONPP_EXPORT std::unique_ptr<Operation> BlazeElemental(const Location & location);
CYLVIONPP_EXPORT std::unique_ptr<Operation> RemoveFromField(const Location & location);

} // namespace operation

} // namespace cylvionpp

#endif // CYLVIONPP_OPERATION_H
