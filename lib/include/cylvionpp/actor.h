#ifndef CYLVIONPP_ACTOR_H
#define CYLVIONPP_ACTOR_H

#include <map>
#include <string>

namespace cylvionpp {

class Content;

struct Action {
    bool end;
    std::map<std::string, std::string> additional;
};

class Actor {
public:
    virtual size_t AnswerIndex(const std::string & question) const = 0;
    virtual Action RevealAction(const Content &) const = 0;
    virtual Action DefendAction(const Content &) const = 0;
};

} // namespace cylvionpp

#endif // CYLVIONPP_ACTOR_H
