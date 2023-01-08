#include "core/vector2d.hpp"

bool isCollideCircleAndAABB(
    vector2d<float>& outClosestPoint,
    vector2d<float> aabb_min,
    vector2d<float> aabb_max,
    vector2d<float> circle_center_pos,
    int radius);

bool isCollideAABBandAABB(
    vector2d<float> aabb1_min,
    vector2d<float> aabb1_max,
    vector2d<float> aabb2_min,
    vector2d<float> aabb2_max);


bool collisionBlockAndBall(struct Block* block, struct Ball* ball);
bool collisionPlayerAndBall(struct Player* player, struct Ball* ball);

//void ballReflectFromAABB(
//    struct Ball& ball,
//    vector2d<float> closestPoint);