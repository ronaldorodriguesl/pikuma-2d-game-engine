#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <glm/glm.hpp>

struct SpriteComponent
{

    int width;
    int heigth;

    SpriteComponent(int width = 0, int heigth = 0)
    {
        this->width = width;
        this->heigth = heigth;
    }
};

#endif