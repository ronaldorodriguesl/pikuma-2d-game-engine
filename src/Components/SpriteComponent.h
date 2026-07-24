#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <glm/glm.hpp>

struct SpriteComponent
{

    std::string assetId;
    int width;
    int heigth;

    SpriteComponent(std::string assetId = "", int width = 0, int heigth = 0)
    {
        this->assetId = assetId;
        this->width = width;
        this->heigth = heigth;
    }
};

#endif