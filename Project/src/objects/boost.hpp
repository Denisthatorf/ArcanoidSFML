#include "Framework.h"
#include "defines.hpp"
#include "core/vector2d.hpp"

#include <memory>
#include <array>

#define BOOST_TYPES_NUM 2
#define BOOST_ANIMATION_NUM 8
#define BOOST_SPRITES_NUM 2 * 8

enum BoostType
{
    HeartMinus = 0,
    HeartPlus = 8
};

class Boost
{
private:
    static std::array<std::unique_ptr<Sprite>, BOOST_SPRITES_NUM> _sprites;
    static int _width, _height;
    static float speed;

public: 
    static void initSprites(float k);

    static void getSize(int& width, int& height);

private:
    unsigned int _animation;

public:
    //TODO: think about int
    vector2d<float> position;

    BoostType type;
    unsigned int _animation_delta;
    bool isNeedToDestroy;

    Boost(vector2d<float> position, BoostType type);

    void draw();
    void update(unsigned int delta);

    vector2d<float> getMaxPosition();
};
