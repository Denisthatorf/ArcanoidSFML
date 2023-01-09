#pragma once 

#include "defines.hpp"
#include "core/vector2d.hpp"

#include <memory>
#include <array>

#define SPRITES_NUM 3

enum PlayerState
{
    PlayerNormal,
    PlayerShort,
    PlayerLong
};

class Player
{
private:
    static std::array<std::unique_ptr<Sprite>, SPRITES_NUM> _sprites;
    static int _width, _height;
    static float speed;

    vector2d<float> _position; 
    uint8_t _animation;
    int8_t _direction_to_move;

public: 
	static void initSprites(float k);	

    Player();

    void draw();
    void update(unsigned int delta_time);
    void move(int move);

    //void setState(PlayerState state);
    void getSize(int& width, int& height) const;
    vector2d<float> getPosition();
    vector2d<float> getMaxPosition();

    void setPosition(vector2d<float> vector);
};
