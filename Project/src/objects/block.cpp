#include "block.hpp"

#include "Framework.h"
#include "helper.hpp"
#include "objects/player.hpp"

//348x128

std::array<std::unique_ptr<Sprite>, COLOR_COUNT> Block::_sprites;
int Block::_width;
int Block::_height;

void Block::initSprites(float k)
{
	_sprites[Yellow]		  = std::make_unique<Sprite>("./data/Block-Yellow.png");
	_sprites[Sea] 		   	  = std::make_unique<Sprite>("./data/Block-Sea.png");
	_sprites[Orange] 		  = std::make_unique<Sprite>("./data/Block-Orange.png");
	_sprites[Green] 		  = std::make_unique<Sprite>("./data/Block-Green.png");
	_sprites[Red] 			  = std::make_unique<Sprite>("./data/Block-Red.png");
	_sprites[Gray] 			  = std::make_unique<Sprite>("./data/Block-Gray.png");

	calculateSpriteSize(_sprites[Yellow], k, _width, _height);

	for (int i = 0; i < COLOR_COUNT; i++)
		_sprites.at(i)->setSpriteSize(_width, _height);
}

Block::Block(vector2d<float> location, BlockColor color)
	:_position(location),
	_color(color),
	_state(Normal)
{}

void Block::draw()
{
	_sprites.at(_color)->drawSprite(_position.x, _position.y);
}

vector2d<float> Block::getPosition() const
    { return _position; }

vector2d<float> Block::getMaxPosition() const
	{ return {_position.x + _width, _position.y + _height }; }

bool Block::isNeedToDestroy() const
	{ return _state == Crashed; }

void Block::getBlockSize(int& width, int& height)
	{ width = _width; height = _height; }
