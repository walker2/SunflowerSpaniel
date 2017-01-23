#ifndef FALCONLATINUM_IMAGELOADER_H
#define FALCONLATINUM_IMAGELOADER_H

#include "../GLTexture.h"
#include <string>
namespace Falcon
{
class ImageLoader
{
public:
    static GLTexture loadPNG(std::string &filePath);
};

}

#endif
