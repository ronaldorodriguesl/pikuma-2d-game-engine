#ifndef ASSETSTORE_H
#define ASSETSTORE_H

#include <SDL2/SDL.h>
#include <map>
#include <string>

class AssetStore
{
private:
    std::map<std::string, SDL_Texture *> textures;

public:
    AssetStore();
    ~AssetStore();

    void ClearAssets();
    void AddTexture(SDL_Renderer *renderer, const std::string &assetId, const std::string &filepath);
    SDL_Texture *GetTexture(const std::string &assetsId);
};

#endif