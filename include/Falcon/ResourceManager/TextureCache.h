#ifndef FALCONLATINUM_TEXTURECACHE_H
#define FALCONLATINUM_TEXTURECACHE_H

#include <map>
#include "../2D/GLTexture.h"
namespace Falcon {
    class TextureCache {
    public:
        TextureCache() {};

        ~TextureCache() {};

        GLTexture getTexture(std::string filePath);

    private:
        std::map<std::string, GLTexture> textureMap;
    };
}

#endif
