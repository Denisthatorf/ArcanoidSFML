#include "defines.hpp"
#include "Framework.h"

void calculateSpriteSize(Sprite *s, float k, int& out_width, int& out_height)
{
    int s_w, s_h;
    getSpriteSize(s, s_w, s_h);

    out_width = s_w * k;
    out_height = s_h * k;
}

void setSpriteSizeByK(Sprite *s, float k)
{
    int s_w, s_h;
    getSpriteSize(s, s_w, s_h);

    int width = s_w * k;
    int height = s_h * k;

    setSpriteSize(s, width, height);
}