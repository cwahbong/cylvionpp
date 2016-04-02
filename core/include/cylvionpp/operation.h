#ifndef CYLVIONPP_OPERATION_H
#define CYLVIONPP_OPERATION_H

#include <memory>
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

namespace operation {

    std::unique_ptr<Operation> PlayerDraw(size_t count);
    std::unique_ptr<Operation> PlayerDiscardHand(size_t idx);
    std::unique_ptr<Operation> PutCylvan(size_t idx, size_t row, size_t col);
    std::unique_ptr<Operation> RevealRavage(size_t row);
    std::unique_ptr<Operation> MoveElemental(size_t fromRow, size_t fromCol, size_t toRow, size_t toCol);
    std::unique_ptr<Operation> MoveOutElemental(size_t row, size_t col);
    std::unique_ptr<Operation> BlazeElemental(size_t row, size_t col);
    std::unique_ptr<Operation> RemoveFromField(size_t row, size_t col);

} // namespace operation

} // namespace core
} // namespace cylvionpp

#endif // CYLVIONPP_OPERATION_H
