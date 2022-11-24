#include "map.hpp"
#include "Framework.h"
#include "objects/boost.hpp"
#include <cstdlib>

Sprite* Map::_sprites[MAP_SPRITES_NUM];
int Map::_gate_padding;
int Map::_border;

Map::Map(int width, int height, std::vector<struct Boost>& boosts) 
    : width(width), height(height), _boosts(boosts) 
{
}

void Map::initSprites(float k)
{
    _sprites[MapBackground] = createSprite("./data/Field-Blue.png");

    _sprites[MapWallHorizontal] = createSprite("./data/Wall-Horizontal.png");
    _sprites[MapWallVerticall] = createSprite("./data/Wall-Vertical.png");

    _sprites[MapEdgeLeft] = createSprite("./data/Edge-Left.png");
    _sprites[MapEngeRight] = createSprite("./data/Edge-Right.png");

    _sprites[MapGateVertical] = createSprite("./data/Gate-Vertical.png");

    char gate[] = "./data/Gate .png";
    for(int i = 0; i < MAP_BOOST_GATE_ANIMATION; i++)
    {
        gate[11] = i+1 + '0';
        _sprites[MapGateHorizontal + i] = createSprite(gate);
    }

    for(int i = 0; i < MAP_SPRITES_NUM; i++)
        setSpriteSizeByK(_sprites[i], k);

    int gate_w, gate_h;
    getSpriteSize(_sprites[MapGateHorizontal], gate_w, gate_h);
    _gate_padding = gate_w / MAP_GATE_PIXELS * (MAP_GATE_PADDING + MAP_GATE_MAIN_PART / 6);
    
    _border = gate_h;
}

void Map::destroySprites()
{
    for(int i = 0; i < MAP_SPRITES_NUM; i++)
        destroySprite(_sprites[i]);
}

void Map::update(unsigned int delta)
{
    //TODO: make as in boost
    if(_gate_animation != -1)
    {
        _animation_delta += delta;
        if(_animation_delta > 500)
        {
            _animation_delta = 0;
            _gate_animation += 1;
        }
    }
    if(_gate_animation == 6)
    {
        _gate_animation = -1;
        _boosts.push_back( Boost({(float)(_span_gate_position_x + _gate_padding), 0}, BoostType::HeartPlus) );
    }
}

void Map::draw()
{
    drawBackground();
    drawWalls();
}

void Map::spanBoost()
{
    _gate_animation = 0;
    _animation_delta = 0;
    _random_gate = rand() % 5;
}

inline void Map::drawWalls()
{
    int edge_w, edge_h;
    getSpriteSize(_sprites[MapEdgeLeft], edge_w, edge_h);
    
    //DROW EDGES
    drawSprite(_sprites[MapEdgeLeft], 0, 0);
    drawSprite(_sprites[MapEngeRight], width - edge_w, 0);

    drawRightAndLeftWalls(edge_h);
    drawTopWall(edge_w);    
}

inline void Map::drawBackground()
{
    int field_w, field_h;
    getSpriteSize(_sprites[MapBackground], field_w, field_h);

    for(int i = 0; i < width; i += field_w)
    {
        for(int j = 0; j < height; j += field_h)
        {
            drawSprite(_sprites[MapBackground], i, j);
        }
    }
}

inline void Map::drawRightAndLeftWalls(int edge_h)
{
    int wall_w, wall_h;
    getSpriteSize(_sprites[MapWallVerticall], wall_w, wall_h);

    int gate_w, gate_h;
    getSpriteSize(_sprites[MapGateVertical], gate_w, gate_h);
    
    int position_w = 0, position_h = edge_h;
    int sprite_num = 0;
    while(true)
    {
        if(position_h >= height)
        {
            int position_w_temp = width - wall_w;
            if(position_w == position_w_temp)
            {
               break;
            }
            position_w = position_w_temp;
            position_h = edge_h;
        }

        if(sprite_num % 3)
        {
            drawSprite(_sprites[MapWallVerticall], position_w, position_h);
            position_h += wall_h;
        }
        else
        {
            drawSprite(_sprites[MapGateVertical], position_w, position_h);
            position_h += gate_h;
        }

        sprite_num += 1;
    }


}

inline void Map::drawTopWall(int edge_w)
{
    int wall_w, wall_h;
    getSpriteSize(_sprites[MapWallHorizontal], wall_w, wall_h);

    int gate_w, gate_h;
    getSpriteSize(_sprites[MapGateHorizontal], gate_w, gate_h);

    for(int w = edge_w, sprite_num = 0, gate_num = 1; 
        w <= width - edge_w;
         sprite_num++)
    {
        if(sprite_num % 3)
        {
            drawSprite(_sprites[MapWallHorizontal], w, 0);
            w += wall_w;
        }
        else
        {
            if(gate_num == _random_gate 
                && _gate_animation != -1)
            {
                drawSprite(_sprites[MapGateHorizontal + _gate_animation], w, 0);
                _span_gate_position_x = w;
            }
            else 
            {
                drawSprite(_sprites[MapGateHorizontal], w, 0);
            }
            w += gate_w;
            gate_num += 1;
        }
    }
}

int Map::getBorder()
    { return _border; }