#ifndef CYLVIONPP_INTRO_H
#define CYLVIONPP_INTRO_H

#include <memory>

namespace cylvionpp {

class CardFactory;
class Content;

std::unique_ptr<Content>
MakeIntroContent(CardFactory & cardFactory);

// TODO MakeFullGame

} // namespace cylvionpp

#endif // CYLVIONPP_INTRO_H
