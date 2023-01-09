#include "defines.hpp"
#include "core/vector2d.hpp"

#include <vector>
#include <array>
#include <memory>

#define MAP_BOOST_GATE_ANIMATION 6
#define MAP_SPRITES_NUM 12

#define MAP_GATE_PIXELS 34
#define MAP_GATE_PADDING 6
#define MAP_GATE_MAIN_PART 22

enum MapSprites
{
   MapBackground,
   MapEdgeLeft, MapEngeRight,
   MapWallVerticall, MapWallHorizontal,
   MapGateVertical, MapGateHorizontal
};

class Map
{
private:
    static std::array<std::unique_ptr<Sprite>, MAP_SPRITES_NUM> _sprites;
    static int _gate_padding;
    static int _border;

public:
    static void initSprites(float k);

private:
    unsigned int _animation_delta = 0;
    int _gate_animation = -1;
    int _random_gate = -1;
    int _span_gate_position_x = 0;

    std::vector<struct Boost>& _boosts;

public:
    const int width;
    const int height;

public:
    Map(int width, int height, std::vector<struct Boost>& boosts);

    void update(unsigned int delta);
    void draw();
    void spanBoost();
    int getBorder();

private:
    inline void drawBackground();
    inline void drawWalls();
    inline void drawRightAndLeftWalls(int edge_height);
    inline void drawTopWall(int edge_width);
};
