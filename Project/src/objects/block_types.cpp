#include "block_types.hpp"
#include "core/vector2d.hpp"

static unsigned int normal_block_count = 0;

Undestroyable_Block::Undestroyable_Block(vector2d<float> location) 
    : Block(location, Gray) {}

void Undestroyable_Block::crash()
{
    if(normal_block_count == 0)
        _state = Crashed;
}

Normal_Block::Normal_Block(vector2d<float> location, BlockColor color) 
    : Block(location, color) 
    { normal_block_count++; }

Normal_Block::~Normal_Block() 
    { normal_block_count--; }

void Normal_Block::crash()
{ 
    normal_block_count--;
    _state = Crashed;
}