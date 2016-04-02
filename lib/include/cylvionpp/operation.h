#ifndef CYLVIONPP_OPERATION_H
#define CYLVIONPP_OPERATION_H

#include "cylvionpp_export.h"

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

CYLVIONPP_EXPORT std::unique_ptr<Operation> PlayerDraw(size_t count);
CYLVIONPP_EXPORT std::unique_ptr<Operation> PlayerDiscardHand(size_t idx);
CYLVIONPP_EXPORT std::unique_ptr<Operation> PutCylvan(size_t idx, size_t row, size_t col);
CYLVIONPP_EXPORT std::unique_ptr<Operation> RevealRavage(size_t row);
CYLVIONPP_EXPORT std::unique_ptr<Operation> MoveElemental(size_t fromRow, size_t fromCol, size_t toRow, size_t toCol);
CYLVIONPP_EXPORT std::unique_ptr<Operation> MoveOutElemental(size_t row, size_t col);
CYLVIONPP_EXPORT std::unique_ptr<Operation> BlazeElemental(size_t row, size_t col);
CYLVIONPP_EXPORT std::unique_ptr<Operation> RemoveFromField(size_t row, size_t col);

} // namespace operation

} // namespace cylvionpp

#endif // CYLVIONPP_OPERATION_H
