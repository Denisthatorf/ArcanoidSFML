#include "map.hpp"
#include "Framework.h"
#include "helper.hpp"
#include "objects/boost.hpp"
#include <cstdlib>

std::array<std::unique_ptr<Sprite>, MAP_SPRITES_NUM> Map::_sprites;

int Map::_gate_padding;
int Map::_border;

Map::Map(int width, int height, std::vector<struct Boost>& boosts) 
    : width(width), height(height), _boosts(boosts) 
{}

void Map::initSprites(float k)
{
    _sprites[MapBackground]     = std::make_unique<Sprite>("./data/Field-Blue.png");
    _sprites[MapWallHorizontal] = std::make_unique<Sprite>("./data/Wall-Horizontal.png");
    _sprites[MapWallVerticall]  = std::make_unique<Sprite>("./data/Wall-Vertical.png");
    _sprites[MapEdgeLeft]       = std::make_unique<Sprite>("./data/Edge-Left.png");
    _sprites[MapEngeRight]      = std::make_unique<Sprite>("./data/Edge-Right.png");
    _sprites[MapGateVertical]   = std::make_unique<Sprite>("./data/Gate-Vertical.png");

    char gate[] = "./data/Gate .png";
    for(int i = 0; i < MAP_BOOST_GATE_ANIMATION; i++)
    {
        gate[11] = i+1 + '0';
        _sprites.at(MapGateHorizontal + i) = std::make_unique<Sprite>(gate);
    }

    for(int i = 0; i < MAP_SPRITES_NUM; i++)
        setSpriteSizeByK(_sprites[i], k);

    int gate_w, gate_h;
    _sprites.at(MapGateHorizontal)->getSpriteSize(gate_w, gate_h);
    _gate_padding = gate_w / MAP_GATE_PIXELS * (MAP_GATE_PADDING + MAP_GATE_MAIN_PART / 6);
    
    _border = gate_h;
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
    _sprites.at(MapEdgeLeft)->getSpriteSize(edge_w, edge_h);
    
    //DROW EDGES
    _sprites.at(MapEdgeLeft)->drawSprite( 0, 0);
    _sprites.at(MapEngeRight)->drawSprite(width - edge_w, 0);

    drawRightAndLeftWalls(edge_h);
    drawTopWall(edge_w);    
}

inline void Map::drawBackground()
{
    int field_w, field_h;
    _sprites.at(MapBackground)->getSpriteSize( field_w, field_h);

    for(int i = 0; i < width; i += field_w)
    {
        for(int j = 0; j < height; j += field_h)
        {
            _sprites.at(MapBackground)->drawSprite(i, j);
        }
    }
}

inline void Map::drawRightAndLeftWalls(int edge_h)
{
    int wall_w, wall_h;
    _sprites.at(MapWallVerticall)->getSpriteSize(wall_w, wall_h);

    int gate_w, gate_h;
    _sprites.at(MapGateVertical)->getSpriteSize(gate_w, gate_h);
    
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
            _sprites.at(MapWallVerticall)->drawSprite(position_w, position_h);
            position_h += wall_h;
        }
        else
        {
            _sprites.at(MapGateVertical)->drawSprite(position_w, position_h);
            position_h += gate_h;
        }

        sprite_num += 1;
    }


}

inline void Map::drawTopWall(int edge_w)
{
    int wall_w, wall_h;
    _sprites.at(MapWallHorizontal)->getSpriteSize(wall_w, wall_h);

    int gate_w, gate_h;
    _sprites.at(MapGateHorizontal)->getSpriteSize(gate_w, gate_h);

    for(int w = edge_w, sprite_num = 0, gate_num = 1; 
        w <= width - edge_w;
         sprite_num++)
    {
        if(sprite_num % 3)
        {
            _sprites.at(MapWallHorizontal)->drawSprite( w, 0);
            w += wall_w;
        }
        else
        {
            if(gate_num == _random_gate 
                && _gate_animation != -1)
            {
                _sprites.at(MapGateHorizontal + _gate_animation)->drawSprite( w, 0);
                _span_gate_position_x = w;
            }
            else 
            {
                _sprites.at(MapGateHorizontal)->drawSprite(w, 0);
            }
            w += gate_w;
            gate_num += 1;
        }
    }
}

int Map::getBorder()
    { return _border; }
