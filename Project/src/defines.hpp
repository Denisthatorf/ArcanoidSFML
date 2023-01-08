#pragma once

#include <core/vector2d.hpp>
#include <stdint.h>

class Sprite;

void calculateSpriteSize(Sprite *s, float k, int& out_width, int& out_height);
void setSpriteSizeByK(Sprite *s, float k);