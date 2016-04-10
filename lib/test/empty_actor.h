#ifndef CYLVIONPP_TEST_EMPTY_ACTOR
#define CYLVIONPP_TEST_EMPTY_ACTOR

#include <cylvionpp/actor.h>

class EmptyActor: public cylvionpp::Actor {
public:
    cylvionpp::Index AnswerIndex(const std::string &) const override { return 0; }
    cylvionpp::Action RevealAction(const cylvionpp::Content &) const override { return {true, {}}; }
    cylvionpp::Action DefendAction(const cylvionpp::Content &) const override { return {true, {}}; }
};

#endif // CYLVIONPP_TEST_EMPTY_ACTOR
