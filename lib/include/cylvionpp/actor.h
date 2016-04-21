#ifndef CYLVIONPP_ACTOR_H
#define CYLVIONPP_ACTOR_H

#include "cylvionpp_export.h"
#include "types.h"

#include <map>
#include <string>

namespace cylvionpp {

class Content;

struct CYLVIONPP_EXPORT Action {
    bool end;
    std::map<std::string, std::string> additional;
};

class CYLVIONPP_EXPORT Actor {
public:
    virtual Index AnswerIndex(const std::string & question, const Content &) const = 0;
    virtual Action RevealAction(const Content &) const = 0;
    virtual Action DefendAction(const Content &) const = 0;
};

} // namespace cylvionpp

#endif // CYLVIONPP_ACTOR_H
