#ifndef CYLVIONPP_DESERTIONS_H
#define CYLVIONPP_DESERTIONS_H

#include "cylvionpp_export.h"
#include "types.h"

#include <memory>

namespace cylvionpp {

class CYLVIONPP_EXPORT Desertions {
public:
    virtual ~Desertions() = 0;

    virtual bool Empty() const = 0;
    virtual unsigned Size() const = 0;

    virtual Index Peek() const = 0;
    virtual Index Peek(Index idx) const = 0;
    virtual void Push(Index) = 0;
    virtual Index Pop() = 0;
    virtual void Shuffle() = 0;

    static std::unique_ptr<Desertions> New();
};

} // namespace cylvionpp

#endif // CYLVIONPP_DESERTIONS_H
