#include "defines.hpp"
#include "helper.hpp"

void calculateSpriteSize(std::unique_ptr<Sprite>& s, float k, int& out_width, int& out_height)
{
    int s_w, s_h;
    s->getSpriteSize(s_w, s_h);

    out_width = s_w * k;
    out_height = s_h * k;
}

void setSpriteSizeByK(std::unique_ptr<Sprite>& s, float k)
{
    int s_w, s_h;
    s->getSpriteSize(s_w, s_h);

    int width = s_w * k;
    int height = s_h * k;

    s->setSpriteSize(width, height);
}
