#pragma once 
#include "defines.hpp"
#include <Framework.h>

#include <memory>

void calculateSpriteSize(std::unique_ptr<Sprite>& s, float k, int& out_width, int& out_height);
void setSpriteSizeByK(std::unique_ptr<Sprite>& s, float k);
