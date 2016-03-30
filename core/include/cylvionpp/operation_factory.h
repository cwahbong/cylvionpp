#ifndef CYLVIONPP_OPERATION_FACTORY_H
#define CYLVIONPP_OPERATION_FACTORY_H

#include <memory>

namespace cylvionpp {
namespace core {

class Operation;

class OperationFactory {
public:
    virtual ~OperationFactory() = 0;

    virtual std::unique_ptr<Operation> PlayerDraw(size_t count) = 0;
    virtual std::unique_ptr<Operation> MoveElemental(size_t fromRow, size_t fromCol, size_t toRow, size_t toCol) = 0;
    virtual std::unique_ptr<Operation> MoveOutElemental(size_t row, size_t col) = 0;

    static std::unique_ptr<OperationFactory> New();
};

} // namespace core
} // namespace cylvionpp

#endif // CYLVIONPP_OPERATION_FACTORY_H
