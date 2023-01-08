#include "stats.hpp"
#include "Framework.h"
#include "helper.hpp"

Sprite* Stats::heart_sprite;

void Stats::initSprites(float k)
{
    heart_sprite = createSprite("./data/Heart.png");
    setSpriteSizeByK(heart_sprite, k / 2);
}

void Stats::destroySprites()
{
    destroySprite(heart_sprite);
}

void Stats::draw()
{
    int width, height;
    getSpriteSize(heart_sprite, width, height);

    for (int i = 0; i < lives; i++)
        drawSprite(heart_sprite, end_position.x - width * i, end_position.y);
}

void Stats::setBorder(vector2d<int> border_pos, int margin)
{
    int width, height;
    getSpriteSize(heart_sprite, width, height);
    end_position = { border_pos.x - width - margin, border_pos.y + margin };
    margin = margin;
}

void Stats::plusForScore()
{
    if(destroyed_in_row >= 3)
        score += 3;
    else
        score++;

    destroyed_in_row++;
}