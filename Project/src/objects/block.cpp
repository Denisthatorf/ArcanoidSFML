#include "block.hpp"

#include "Framework.h"
#include "defines.hpp"
#include "objects/player.hpp"

//348x128

Sprite* Block::_sprites[COLOR_COUNT];
int Block::_width;
int Block::_height;

void Block::initSprites(float k)
{
	_sprites[Yellow]		  = createSprite("./data/Block-Yellow.png");
	_sprites[Sea] 		   	  = createSprite("./data/Block-Sea.png");
	_sprites[Orange] 			  = createSprite("./data/Block-Orange.png");
	_sprites[Green] 			  = createSprite("./data/Block-Green.png");
	_sprites[Red] 			  = createSprite("./data/Block-Red.png");
	_sprites[Gray] 			  = createSprite("./data/Block-Gray.png");

	calculateSpriteSize(_sprites[Yellow], k, _width, _height);

	for (int i = 0; i < COLOR_COUNT; i++)
		setSpriteSize(_sprites[i], _width, _height);
}

Block::Block(vector2d<float> location, BlockColor color)
	:_position(location),
	_color(color),
	_state(Normal)
{}

void Block::destroySprites()
{
	for (int i = 0; i < COLOR_COUNT; i++)
		destroySprite(_sprites[i]);
}

void Block::draw()
{
	drawSprite(_sprites[_color], _position.x, _position.y);
}

vector2d<float> Block::getPosition() const
    { return _position; }

vector2d<float> Block::getMaxPosition() const
	{ return {_position.x + _width, _position.y + _height }; }

bool Block::isNeedToDestroy() const
	{ return _state == Crashed; }

void Block::getBlockSize(int& width, int& height)
	{ width = _width; height = _height; }