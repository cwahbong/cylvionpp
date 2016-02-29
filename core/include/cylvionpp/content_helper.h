#ifndef CYLVIONPP_CONTENT_HELPER_H
#define CYLVIONPP_CONTENT_HELPER_H

#include <cstdlib>

namespace cylvionpp {
namespace core {

class Actor;
class Content;

void StartingShuffle(Content & content);
void PlayerDraw(Content & content);
void MoveLeftAllElementals(Content & content);
bool ActRevealActions(Content & content, const Actor & actor);
bool ActDefendActions(Content & content, const Actor & actor);
bool DiscardChooseFromHand(Content & content, const Actor & actor);

void MoveOutElemental(Content & content, size_t fromRow, size_t fromCol);

} // namespace core
} // namespace cylvionpp

#endif // CYLVIONPP_CONTENT_HELPER_H
