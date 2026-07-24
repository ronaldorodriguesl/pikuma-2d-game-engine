#include "./AssetStore.h"
#include "../Logger/Logger.h"
#include <SDL2/SDL_image.h>

AssetStore::AssetStore()
{
    Logger::Log("AssetStore constructor called!");
}

AssetStore::~AssetStore()
{
    ClearAssets();
    Logger::Log("AssetStore constructor called!");
}

void AssetStore::ClearAssets()
{
    for (auto texture : textures)
    {
        SDL_DestroyTexture(texture.second);
    }

    textures.clear();
}

void AssetStore::AddTexture(SDL_Renderer *renderer, const std::string &assetId, const std::string &filepath)
{
    SDL_Surface *surface = IMG_Load(filepath.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Add texture to the map
    textures.emplace(assetId, texture);

    Logger::Log("Next texture added to the Asset Store with Id = " + assetId);
}

SDL_Texture *AssetStore::GetTexture(const std::string &assetId)
{
    return textures[assetId];
}
