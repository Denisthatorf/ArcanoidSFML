#include "collision.hpp"

#include "objects/ball.hpp"
#include "objects/block.hpp"
#include "objects/player.hpp"

bool isCollideCircleAndAABB(
    vector2d<float>& outClosestPoint,
    vector2d<float> aabb_min,
    vector2d<float> aabb_max,
    vector2d<float> circle_center_pos,
    int radius)
{
    outClosestPoint = circle_center_pos;

    if(circle_center_pos.x < aabb_min.x)    
        outClosestPoint.x = aabb_min.x;
    else if (circle_center_pos.x > aabb_max.x)    
        outClosestPoint.x = aabb_max.x;

    if(circle_center_pos.y < aabb_min.y)    
        outClosestPoint.y = aabb_min.y;
    else if (circle_center_pos.y > aabb_max.y)    
        outClosestPoint.y = aabb_max.y;

    vector2d<float> circleToBox
        = circle_center_pos.dest_vector(outClosestPoint);

    return circleToBox.lengthSquered() <= radius * radius;
}

bool isCollideAABBandAABB(
    vector2d<float> aabb1_min,
    vector2d<float> aabb1_max,
    vector2d<float> aabb2_min,
    vector2d<float> aabb2_max)
{
    if(aabb1_min.x < aabb2_max.x &&
       aabb1_max.x > aabb2_min.x &&
       aabb1_min.y < aabb2_max.y &&
       aabb1_max.y > aabb2_min.y)
    {
        return true;
    }

    return false;
}

bool collisionBlockAndBall(Block* block, Ball* ball)
{
	vector2d<float> circle_center_pos = ball->getCenterPosition();
	vector2d<float> closestPoint;

    bool result = isCollideCircleAndAABB(
		closestPoint,
		block->getPosition(), block->getMaxPosition(),
		circle_center_pos, ball->getRadius());

	if(result)
	{
		vector2d<float> normal = closestPoint.dest_vector(circle_center_pos).normalize();
		vector2d<float> velocity = ball->getVelocity().reflect(normal);
		
		ball->setDirection(velocity);
		ball->push(normal);

		//TODO: implement boost when block destroy
		block->crash();
	}

    return result;
}

bool collisionPlayerAndBall(Player* player, Ball* ball)
{
    vector2d<float> circle_center_pos = ball->getCenterPosition();
	vector2d<float> closestPoint;
	
    bool result = isCollideCircleAndAABB (
		closestPoint,
		player->getPosition(), player->getMaxPosition(),
		circle_center_pos, ball->getRadius()
        );

	if(result)
	{
		vector2d<float> normal = closestPoint.dest_vector(circle_center_pos).normalize();
		vector2d<float> velocity = ball->getVelocity().reflect(normal);
		
		ball->setDirection(velocity);
		ball->push(normal * 3);
    }

    return result;
}



//void ballReflectFromAABB(
//    struct Ball& ball,
//    vector2d<float> closestPoint)
//{
//	vector2d<float> normal = closestPoint.dest_vector(circle_center_pos).normalize();
//	vector2d<float> velocity = ball_velocity.reflect(normal);
//
//    return velocity;
//}