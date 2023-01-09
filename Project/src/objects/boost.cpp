#include "boost.hpp"
#include "Framework.h"
#include "helper.hpp"
#include "core/vector2d.hpp"

std::array<std::unique_ptr<Sprite>, BOOST_SPRITES_NUM> Boost::_sprites;

float Boost::speed = 0.2f;
int Boost::_width;
int Boost::_height;

void Boost::initSprites(float k)
{
    char heartPlus[] = "./data/Boost-Red .png";
    char heartMinus[] = "./data/Boost-Green .png";

    for(int i = 0; i < BOOST_ANIMATION_NUM; i++)
    {
        heartPlus[16] = i+1 + '0';
        heartMinus[18] = i+1 + '0';

        _sprites[HeartMinus + i] = std::make_unique<Sprite>(heartPlus);
        _sprites[HeartPlus + i]  = std::make_unique<Sprite>(heartMinus);
    }

    calculateSpriteSize(_sprites.at(HeartPlus), k, _width, _height);

    for(int i = 0; i < BOOST_SPRITES_NUM;  i++)
        _sprites.at(i)->setSpriteSize( _width, _height);
}

//BOOST METHODS

Boost::Boost(vector2d<float> position, BoostType type)
    : position(position), 
    type(type),
    _animation(0),
    _animation_delta(0),
    isNeedToDestroy(false)
    {}

void Boost::draw()
{
    _sprites.at(type + _animation)->drawSprite(position.x, position.y);
}

void Boost::update(unsigned int delta)
{
    _animation_delta += delta;
    int animation_plus = _animation_delta / 100;

    if(animation_plus)
    {
        _animation += animation_plus;
        _animation_delta -= 100 * animation_plus;
    }

    if(_animation >= BOOST_ANIMATION_NUM - 1)
    {
        _animation = 0;
    }

    position.y += delta * speed;
}

void Boost::getSize(int& width, int& height)
    { width = _width; height = _height; }

vector2d<float> Boost::getMaxPosition()
    { return { position.x + _width, position.y + _height }; }
