#ifndef ASSETSTORE_H
#define ASSETSTORE_H

#include <string>
#include <map>
#include <SDL.h>
#include <glm/glm.hpp>

class AssetStore {
    private:
        std::map<std::string, SDL_Texture*> textures;
        
    public:
        AssetStore();
        ~AssetStore();

        void ClearAssets();
        void AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath);
        SDL_Texture* GetTexture(const std::string& assetId);
};

#endif 
