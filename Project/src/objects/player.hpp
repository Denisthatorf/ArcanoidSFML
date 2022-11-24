#pragma once 

#include "defines.hpp"
#include "math/vector2d.hpp"

#define SpritesNum 3

enum PlayerState
{
    PlayerNormal,
    PlayerShort,
    PlayerLong
};

class Player
{
private:
    static Sprite* _sprites[SpritesNum];
    static int _width, _height;
    static float speed;

    vector2d<float> _position; 
    uint8_t _animation;
    int8_t _direction_to_move;

public: 
	static void initSprites(float k);	
    static void destroySprites();

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
