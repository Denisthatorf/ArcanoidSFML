#include "ball.hpp"
#include "Framework.h"
#include "helper.hpp"
#include "core/vector2d.hpp"
#include <features.h>

std::unique_ptr<Sprite> Ball::_sprite;

float Ball::speed = 0.5f;
int Ball::_radius;

void Ball::initSprites(float k)
{
    _sprite = std::make_unique<Sprite>("./data/Ball.png");

    int width, height;
    calculateSpriteSize(_sprite, k, width, height);
    _radius = width / 2;

    _sprite->setSpriteSize(width, height);
}

Ball::Ball()
    : _position({0,0}),
    _velocity({0,0})
{}

void Ball::draw()
{
    _sprite->drawSprite(_position.x, _position.y);
}

void Ball::update(unsigned int delta_time)
{
    _position += ( _velocity * delta_time) ;
}

void Ball::push(vector2d<float> vector)
{
    _position.x += vector.x;
    _position.y += vector.y;
}

void Ball::setDirection(vector2d<float> vector)
    { _velocity = vector.normalize() * speed; }

void Ball::setVelocity(vector2d<float> vector)
    { _velocity = vector; }

void Ball::setPosition(vector2d<float> vector)
    {_position = vector; }
    
void Ball::setCenterPosition(vector2d<float> vector)
{
    int radius = getRadius();
    _position = {vector.x - radius, vector.y + radius}; 
}

vector2d<float> Ball::getPosition() const
    { return _position;}

vector2d<float> Ball::getCenterPosition() const
    { return { _position.x + _radius, _position.y + _radius }; }

//vector2d<float> Ball::getDirection()
//    { return _direction.normalize(); }

vector2d<float> Ball::getVelocity() const
    { return _velocity; }

int Ball::getRadius() const
    { return _radius; }
