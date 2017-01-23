#ifndef FALCONLATINUM_RESOURCEMANAGER_H
#define FALCONLATINUM_RESOURCEMANAGER_H


#include "TextureCache.h"
#include <string>
namespace Falcon
{
    class ResourceManager
    {
    public:
        static GLTexture getTexture(std::string filePath);

        static GLuint boundTexture;
    private:
        static TextureCache m_textureCache;

    };
}

#endif