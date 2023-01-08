#include "player.hpp"
#include "Framework.h"
#include "core/vector2d.hpp"
#include "core/log.hpp"
#include <cstdint>


Sprite* Player::_sprites[SpritesNum];
float Player::speed = 1;
int Player::_width;
int Player::_height;

void Player::initSprites(float k)
{
    //TODO: !!!
    _sprites[PlayerNormal] = createSprite("./data/StarShip.png");
    //_sprites[PlayerShort] = createSprite("./data/StarShip.png");
    //_sprites[PlayerLong] = createSprite("./data/StarShip.png");
	
    calculateSpriteSize(_sprites[PlayerNormal], k, _width, _height);

    //for(uint8_t i = 0; i < SpritesNum; i++)
    setSpriteSize(_sprites[PlayerNormal], _width, _height);
}

void Player::destroySprites()
{
    //TODO: !!!
    //for(uint8_t i = 0; i < SpritesNum; i++)
    destroySprite(_sprites[PlayerNormal]);
}

Player::Player()
    : _animation (0),
    _position ( {0, 0} ),
    _direction_to_move(0)
{}

void Player::draw()
{
    //TODO: !!!
    //Sprite* sprite = _sprites[_animation % 3];

    Sprite* sprite = _sprites[PlayerNormal];
    drawSprite(sprite, _position.x, _position.y);
}

void Player::update(unsigned int delta_time)
{
    //TODO: think
    //_animation += 1;

    _position.x += _direction_to_move * speed * delta_time;
    _direction_to_move = 0;
}

void Player::move(int move)
    { _direction_to_move = move; }
   
void Player::setPosition(vector2d<float> vector)
    {_position = vector; }
    
void Player::getSize(int& width, int& height) const
    { width = _width, height = _height;}

vector2d<float> Player::getPosition()
    { return _position; }

vector2d<float> Player::getMaxPosition()
{ return {_position.x + _width, _position.y + _height}; }

