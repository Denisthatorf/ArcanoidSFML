#include "math/vector2d.hpp"
#include "objects/block.hpp"

class Undestroyable_Block : public Block
{
public:
    Undestroyable_Block(vector2d<float> location);
    void crash() override;
};

class Normal_Block : public Block
{
public:
    Normal_Block(vector2d<float> location, BlockColor color);
    ~Normal_Block();
    void crash() override;
};