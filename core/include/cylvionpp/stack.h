#ifndef CYLVIONPP_STACK_H
#define CYLVIONPP_STACK_H

namespace cylvionpp {
namespace core {

class Stack {
public:
    virtual bool Empty() const = 0;
    virtual unsigned Size() const = 0;

    virtual const std::unique_ptr<Card> & Peek() const = 0;
    virtual void Push(std::unique_ptr<Card> &&) = 0;
    virtual std::unique_ptr<Card> Pop() = 0;
    virtual void Shuffle() = 0;

    static std::unique_ptr<Stack> New();
};

} // namespace core
} // namespace cylvionpp

#endif // CYLVIONPP_STACK_H
