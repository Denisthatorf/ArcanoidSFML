#include "defines.hpp"

#include <vector>

#define COLOR_COUNT 6

//MAKE BROKEN ANIMATION
enum BlockState : uint8_t
{
	Normal = 0,
	Broked = 1,
	Crashed = 2
};

enum BlockColor : uint8_t
{
	Sea,
	Red,
	Green,
	Orange,
	Yellow,
	Gray
};

struct Boost;

class Block
{
protected:
	static int _width;
	static int _height;
	static unsigned int _block_num;
	static Sprite* _sprites[COLOR_COUNT];

	vector2d<float> _position;
	BlockColor _color;
	BlockState _state;

public:
	Block(vector2d<float> location, BlockColor color);
    virtual void crash() = 0;

    void draw();

	bool isNeedToDestroy() const;
	vector2d<float> getPosition() const;
	vector2d<float> getMaxPosition() const;

public:
	static void initSprites(float k);	
	static void destroySprites();
	static void getBlockSize(int& width, int& height);
};
