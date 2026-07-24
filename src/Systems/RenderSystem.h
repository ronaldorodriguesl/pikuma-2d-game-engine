#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <SDL2/SDL.h>

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

class RenderSystem : public System
{
private:
public:
    RenderSystem()
    {
        RequireComponent<TransformComponent>();
        RequireComponent<SpriteComponent>();
    }
    void Update(SDL_Renderer *renderer)
    {
        for (auto entity : GetSystemEntities())
        {
            const auto transform = entity.GetComponent<TransformComponent>();
            const auto sprite = entity.GetComponent<SpriteComponent>();
        }
    }
};

#endif