#include "player.hpp"
#include "Framework.h"
#include "core/vector2d.hpp"
#include "logger.hpp"
#include "helper.hpp"
#include <cstdint>

std::array<std::unique_ptr<Sprite>, SPRITES_NUM> Player::_sprites;

float Player::speed = 1;
int Player::_width;
int Player::_height;

void Player::initSprites(float k)
{
    //TODO: Player animation
    _sprites[PlayerNormal] = std::make_unique<Sprite>("./data/StarShip.png");

    calculateSpriteSize(_sprites.at(PlayerNormal), k, _width, _height);

    _sprites.at(PlayerNormal)->setSpriteSize(_width, _height);
}

Player::Player()
    : _animation (0),
    _position ( {0, 0} ),
    _direction_to_move(0)
{}

void Player::draw()
{
    //TODO: Player animation
    _sprites.at(PlayerNormal)->drawSprite(_position.x, _position.y);
}

void Player::update(unsigned int delta_time)
{
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

