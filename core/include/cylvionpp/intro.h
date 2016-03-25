#ifndef CYLVIONPP_INTRO_H
#define CYLVIONPP_INTRO_H

#include <memory>

namespace cylvionpp {
namespace core {

class Content;

std::unique_ptr<Content>
MakeIntroContent();

// TODO MakeFullGame

} // namespace core
} // namespace cylvionpp

#endif // CYLVIONPP_INTRO_H
